#include "QsLog.h"
#include "Mouse3DInput.h"

#include <QApplication>

#define LOGITECH_VENDOR_ID 0x46d
#define _CONSTANT_INPUT_PERIOD 0

#ifndef RIDEV_DEVNOTIFY
#define RIDEV_DEVNOTIFY 0x00002000
#endif

#define _TRACE_WM_INPUT_PERIOD 0
#define _TRACE_RI_TYPE 0
#define _TRACE_RIDI_DEVICENAME 0
#define _TRACE_RIDI_DEVICEINFO 0
#define _TRACE_RI_RAWDATA 0
#define _TRACE_3DINPUT_PERIOD 0

#ifdef _WIN64
typedef unsigned __int64 QWORD;
#endif

// object angular velocity per mouse tick 0.008 milliradians per second per count	마우스 틱 당 개체 각속도 1 초당 0.008 밀리 라디안
static const double k3dmouseAngularVelocity = 8.0e-6; // radians per second per count	초당 라디안 / 회

static const int kTimeToLive = 5;

enum e3dconnexion_pid {
   eSpacePilot = 0xc625,
   eSpaceNavigator = 0xc626,
   eSpaceExplorer = 0xc627,
   eSpaceNavigatorForNotebooks = 0xc628,
   eSpacePilotPRO = 0xc629
};

enum e3dmouse_virtual_key
{
   V3DK_INVALID=0
   , V3DK_MENU=1, V3DK_FIT
   , V3DK_TOP, V3DK_LEFT, V3DK_RIGHT, V3DK_FRONT, V3DK_BOTTOM, V3DK_BACK
   , V3DK_CW, V3DK_CCW
   , V3DK_ISO1, V3DK_ISO2
   , V3DK_1, V3DK_2, V3DK_3, V3DK_4, V3DK_5, V3DK_6, V3DK_7, V3DK_8, V3DK_9, V3DK_10
   , V3DK_ESC, V3DK_ALT, V3DK_SHIFT, V3DK_CTRL
   , V3DK_ROTATE, V3DK_PANZOOM, V3DK_DOMINANT
   , V3DK_PLUS, V3DK_MINUS
};

struct tag_VirtualKeys
{
   e3dconnexion_pid pid;
   size_t nKeys;
   e3dmouse_virtual_key *vkeys;
};

static const e3dmouse_virtual_key SpaceExplorerKeys [] =
{
   V3DK_INVALID     // there is no button 0	// 버튼이 없다. 0
   , V3DK_1, V3DK_2
   , V3DK_TOP, V3DK_LEFT, V3DK_RIGHT, V3DK_FRONT
   , V3DK_ESC, V3DK_ALT, V3DK_SHIFT, V3DK_CTRL
   , V3DK_FIT, V3DK_MENU
   , V3DK_PLUS, V3DK_MINUS
   , V3DK_ROTATE
};

static const e3dmouse_virtual_key SpacePilotKeys [] =
{
   V3DK_INVALID
   , V3DK_1, V3DK_2, V3DK_3, V3DK_4, V3DK_5, V3DK_6
   , V3DK_TOP, V3DK_LEFT, V3DK_RIGHT, V3DK_FRONT
   , V3DK_ESC, V3DK_ALT, V3DK_SHIFT, V3DK_CTRL
   , V3DK_FIT, V3DK_MENU
   , V3DK_PLUS, V3DK_MINUS
   , V3DK_DOMINANT, V3DK_ROTATE
};

static const struct tag_VirtualKeys _3dmouseVirtualKeys[]=
{
   eSpacePilot
   , sizeof(SpacePilotKeys)/sizeof(SpacePilotKeys[0])
   , const_cast<e3dmouse_virtual_key *>(SpacePilotKeys),
   eSpaceExplorer
   , sizeof(SpaceExplorerKeys)/sizeof(SpaceExplorerKeys[0])
   , const_cast<e3dmouse_virtual_key *>(SpaceExplorerKeys)
};

/*!
	Converts a hid device keycode (button identifier) of a pre-2009 3Dconnexion USB device to the standard 3d mouse virtual key definition.

	\a pid USB Product ID (PID) of 3D mouse device
	\a hidKeyCode  Hid keycode as retrieved from a Raw Input packet

	\return The standard 3d mouse virtual key (button identifier) or zero if an error occurs.

	Converts a hid device keycode (button identifier) of a pre-2009 3Dconnexion USB device
	to the standard 3d mouse virtual key definition.
*/

/*
	2009 년 이전 3Dconnexion USB 장치의 숨겨진 장치 키 코드 (단추 식별자)를 표준 3D 마우스 가상 키 정의로 변환합니다.
	\ a pid 3D 마우스 장치의 USB 제품 ID (PID)
	\ a hidKeyCode 원시 입력 패킷에서 검색된 키 코드 숨김
	\ return 표준 3D 마우스 가상 키 (단추 ID) 또는 오류가 발생하면 0입니다.
	2009 년 이전 3Dconnexion USB 장치의 숨겨진 장치 키 코드 (버튼 식별자)를 변환합니다.
	표준 3D 마우스 가상 키 정의.
*/


unsigned short HidToVirtualKey(unsigned long pid, unsigned short hidKeyCode)
{
   unsigned short virtualkey=hidKeyCode;
   for (size_t i=0; i<sizeof(_3dmouseVirtualKeys)/sizeof(_3dmouseVirtualKeys[0]); ++i)
   {
	  if (pid == _3dmouseVirtualKeys[i].pid)
	  {
		 if (hidKeyCode < _3dmouseVirtualKeys[i].nKeys)
			virtualkey = _3dmouseVirtualKeys[i].vkeys[hidKeyCode];
		 else
			virtualkey = V3DK_INVALID;
		 break;
	  }
   }
   // Remaining devices are unchanged	나머지 장치는 변경되지 않습니다.
   return virtualkey;
}


static Mouse3DInput* gMouseInput = 0;

bool Mouse3DInput::RawInputEventFilter(void* msg, long* result)
{
	if (gMouseInput == 0) return false;

	MSG* message = (MSG*)(msg);

	if (message->message == WM_INPUT) {
		HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(message->lParam);
		gMouseInput->OnRawInput(RIM_INPUT,hRawInput);
		if (result != 0)  {
			result = 0;
		}
		return true;
	}

	return false;
}


Mouse3DInput::Mouse3DInput(QWidget* widget) :
									QObject(widget)
{
	fLast3dmouseInputTime = 0;

//	InitializeRawInput(widget->winId());

    //gMouseInput = this;
    //qApp->setEventFilter(Mouse3DInput::RawInputEventFilter);
}

Mouse3DInput::~Mouse3DInput()
{
	if (gMouseInput == this) {
		gMouseInput = 0;
	}
}

/*!	
	Access the mouse parameters structure	마우스 매개 변수 구조에 액세스
*/


I3dMouseParam& Mouse3DInput::MouseParams()
{
	return f3dMouseParams;
}

/*!
	Access the mouse parameters structure	마우스 매개 변수 구조에 액세스
*/
const I3dMouseParam& Mouse3DInput::MouseParams() const
{
	return f3dMouseParams;
}

/*!
	Called with the processed motion data when a 3D mouse event is received

	The default implementation emits a Move3d signal with the motion data		
*/

/*
	3D 마우스 이벤트가 수신 될 때 처리 된 모션 데이터로 호출됩니다.
	기본 구현은 모션 데이터와 함께 Move3d 신호를 내 보냅니다.
*/

void Mouse3DInput::Move3d(HANDLE device, std::vector<float>& motionData)
{
	Q_UNUSED(device);
	emit Move3d(motionData);
}

/*!
	Called when a 3D mouse key is pressed

	The default implementation emits a On3dmouseKeyDown signal with the key code.
*/

/*
	3D 마우스 키를 누를 때 호출됩니다.
	기본 구현은 키 코드와 함께 On3dmouseKeyDown 신호를 내 보냅니다.
*/

void Mouse3DInput::On3dmouseKeyDown(HANDLE device, int virtualKeyCode)
{
	Q_UNUSED(device);
	emit On3dmouseKeyDown(virtualKeyCode);
}

/*!
	Called when a 3D mouse key is released

	The default implementation emits a On3dmouseKeyUp signal with the key code.
*/

/*

	3D 마우스 키를 놓을 때 호출됩니다.
	기본 구현은 키 코드와 함께 On3dmouseKeyUp 신호를 내 보냅니다.
*/

void Mouse3DInput::On3dmouseKeyUp(HANDLE device, int virtualKeyCode)
{
	Q_UNUSED(device);
	emit On3dmouseKeyUp(virtualKeyCode);
}

/*!
	Get an initialized array of PRAWINPUTDEVICE for the 3D devices

	pNumDevices returns the number of devices to register. Currently this is always 1.
 */

/*
	3D 장치 용으로 PRAWINPUTDEVICE의 초기화 된 배열 가져 오기
	pNumDevices는 등록 할 장치 수를 반환합니다. 현재이 값은 항상 1입니다.
*/

static PRAWINPUTDEVICE GetDevicesToRegister(unsigned int* pNumDevices)
{
	// Array of raw input devices to register	등록 할 원시 입력 장치의 배열
	static RAWINPUTDEVICE sRawInputDevices[] = {
		{0x01, 0x08, 0x00, 0x00} // Usage Page = 0x01 Generic Desktop Page, Usage Id= 0x08 Multi-axis Controller	사용 페이지 = 0x01 일반 데스크탑 페이지, 사용 ID = 0x08 다축 컨트롤러
	};

	if (pNumDevices) {
		*pNumDevices = sizeof(sRawInputDevices) / sizeof(sRawInputDevices[0]);
	}

	return sRawInputDevices;
}

/*!
	Detect the 3D mouse	3D 마우스 감지
*/
bool Mouse3DInput::Is3dmouseAttached()
{
	unsigned int numDevicesOfInterest = 0;
	PRAWINPUTDEVICE devicesToRegister = GetDevicesToRegister(&numDevicesOfInterest);

	unsigned int nDevices = 0;

	if (::GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) != 0) {
		return false;
	}

	if (nDevices == 0) return false;

	std::vector<RAWINPUTDEVICELIST> rawInputDeviceList(nDevices);
	if (::GetRawInputDeviceList(&rawInputDeviceList[0], &nDevices, sizeof(RAWINPUTDEVICELIST)) == static_cast<unsigned int>(-1)) {
		return false;
	}

	for (unsigned int i = 0; i < nDevices; ++i) {
		RID_DEVICE_INFO rdi = {sizeof(rdi)};
		unsigned int cbSize = sizeof(rdi);

		if (GetRawInputDeviceInfo(rawInputDeviceList[i].hDevice, RIDI_DEVICEINFO, &rdi, &cbSize) > 0) {
			//skip non HID and non logitec (3DConnexion) devices	비 HID 및 비 logitec (3DConnexion) 장치를 건너 뜁니다.
			if (rdi.dwType != RIM_TYPEHID || rdi.hid.dwVendorId != LOGITECH_VENDOR_ID) {
				continue;
			}

			//check if devices matches Multi-axis Controller	장치가 다축 컨트롤러와 일치하는지 확인
			for (unsigned int j = 0; j < numDevicesOfInterest; ++j) {
				if (devicesToRegister[j].usUsage == rdi.hid.usUsage
						&& devicesToRegister[j].usUsagePage == rdi.hid.usUsagePage) {
					return true;
				}
			}
		}
	}
	return false;
}



/*!
	Initialize the window to recieve raw-input messages

	This needs to be called initially so that Windows will send the messages from the 3D mouse to the window.
*/

/*
	원시 입력 메시지를 수신하도록 창 초기화
	Windows가 3D 마우스에서 창으로 메시지를 보내도록하려면 먼저 호출해야합니다.
*/

bool Mouse3DInput::InitializeRawInput(HWND hwndTarget)
{
	fWindow = hwndTarget;

	// Simply fail if there is no window	윈도우가 없다면 실패한다.
	if (!hwndTarget)  return false;

	unsigned int numDevices = 0;
	PRAWINPUTDEVICE devicesToRegister = GetDevicesToRegister(&numDevices);

	if (numDevices == 0) return false;

	// Get OS version.	OS 버전을 가져옵니다.
	OSVERSIONINFO osvi = {sizeof(OSVERSIONINFO),0};
	::GetVersionEx(&osvi);

	unsigned int cbSize = sizeof (devicesToRegister[0]);
	for (size_t i = 0; i < numDevices; i++) {
		// Set the target window to use
		//devicesToRegister[i].hwndTarget = hwndTarget;

		// If Vista or newer, enable receiving the WM_INPUT_DEVICE_CHANGE message.

/*
		// 사용할 대상 윈도우를 설정합니다.
		// devicesToRegister [i] .hwndTarget = hwndTarget;

		// Vista 이상인 경우 WM_INPUT_DEVICE_CHANGE 메시지 수신을 활성화합니다.
*/

		if (osvi.dwMajorVersion >= 6) {
			devicesToRegister[i].dwFlags |= RIDEV_DEVNOTIFY;
		}
	}
	return (::RegisterRawInputDevices(devicesToRegister, numDevices, cbSize) != FALSE);
}


/*!
	Get the raw input data from Windows

	Includes workaround for incorrect alignment of the RAWINPUT structure on x64 os
	when running as Wow64 (copied directly from 3DConnexion code)
*/

/*
	Windows에서 원시 입력 데이터 가져 오기
	x64 OS에서 RAWINPUT 구조체의 잘못된 정렬에 대한 해결 방법을 포함합니다.
	Wow64 (3DConnexion 코드에서 직접 복사)로 실행하면
*/


UINT Mouse3DInput::GetRawInputBuffer(PRAWINPUT pData, PUINT pcbSize, UINT cbSizeHeader)
{
#ifdef _WIN64
	return ::GetRawInputBuffer(pData, pcbSize, cbSizeHeader);
#else
	BOOL bIsWow64 = FALSE;
	::IsWow64Process(GetCurrentProcess(), &bIsWow64);
	if (!bIsWow64 || pData==NULL) {
		return ::GetRawInputBuffer(pData, pcbSize, cbSizeHeader);
	} else {
		HWND hwndTarget = fWindow; //fParent->winId();

		size_t cbDataSize=0;
		UINT nCount=0;
		PRAWINPUT pri = pData;

		MSG msg;
		while (PeekMessage(&msg, hwndTarget, WM_INPUT, WM_INPUT, PM_NOREMOVE)) {
			HRAWINPUT hRawInput = reinterpret_cast<HRAWINPUT>(msg.lParam);
			size_t cbSize = *pcbSize - cbDataSize;
			if (::GetRawInputData(hRawInput, RID_INPUT, pri, &cbSize, cbSizeHeader) == static_cast<UINT>(-1)) {
				if (nCount==0) {
					return static_cast<UINT>(-1);
				}  else {
					break;
				}
			}
			++nCount;

			// Remove the message for the data just read	방금 읽은 데이터에 대한 메시지를 제거합니다.
			PeekMessage(&msg, hwndTarget, WM_INPUT, WM_INPUT, PM_REMOVE);

			pri = NEXTRAWINPUTBLOCK(pri);
			cbDataSize = reinterpret_cast<ULONG_PTR>(pri) - reinterpret_cast<ULONG_PTR>(pData);
			if (cbDataSize >= *pcbSize) {
				cbDataSize = *pcbSize;
				break;
			}
		}
		return nCount;
	}
#endif
}

/*!
	Process the raw input device data

	On3dmouseInput() does all the preprocessing of the rawinput device data before
	finally calling the Move3d method.
*/

/*
	원시 입력 장치 데이터 처리
	On3dmouseInput ()은 전에 rawinput 장치 데이터의 모든 전처리를 수행합니다.
	마지막으로 Move3d 메서드를 호출합니다.
*/


void Mouse3DInput::On3dmouseInput()
{
	// Don't do any data processing in background	백그라운드에서 데이터 처리를하지 않습니다.
	bool bIsForeground = (::GetActiveWindow() != NULL);
	if (!bIsForeground) {
		// set all cached data to zero so that a zero event is seen and the cached data deleted	모든 캐시 된 데이터를 0으로 설정하여 0 이벤트가 표시되고 캐시 된 데이터가 삭제됩니다.
		for (std::map<HANDLE, TInputData>::iterator it = fDevice2Data.begin(); it != fDevice2Data.end(); it++) {
			it->second.fAxes.assign(6, .0);
			it->second.fIsDirty = true;
		}
	}

	DWORD dwNow = ::GetTickCount();           // Current time;	현재 시간;
	DWORD dwElapsedTime;                      // Elapsed time since we were last here	마지막으로 여기에 있었던 이후의 경과 시간

	if (0 == fLast3dmouseInputTime) {
		dwElapsedTime = 10;                    // System timer resolution	시스템 타이머 해상도
	} else {
		dwElapsedTime = dwNow - fLast3dmouseInputTime;
		if (fLast3dmouseInputTime > dwNow) {
			dwElapsedTime = ~dwElapsedTime+1;
		}
		if (dwElapsedTime<1) {
			dwElapsedTime=1;
		} else if (dwElapsedTime > 500) {
			// Check for wild numbers because the device was removed while sending data	데이터를 보내는 동안 기기가 삭제 되었기 때문에 야생 번호를 확인합니다.
			dwElapsedTime = 10;
		}
	}

#if _TRACE_3DINPUT_PERIOD
    QLOG_INFO() << "On3DmouseInput() period is %dms\n", dwElapsedTime;
#endif

	float mouseData2Rotation = k3dmouseAngularVelocity;
	// v = w * r,  we don't know r yet so lets assume r=1.)	v = w * r, 우리는 아직 r을 모른다. 그래서 r = 1로 가정한다.)
	float mouseData2PanZoom = k3dmouseAngularVelocity;

	// Grab the I3dmouseParam interface	I3dmouseParam 인터페이스를 가져옵니다.
	 I3dMouseParam& i3dmouseParam = f3dMouseParams;
	 // Take a look at the users preferred speed setting and adjust the sensitivity accordingly	사용자가 선호하는 속도 설정을보고 이에 따라 민감도를 조정하십시오.
	 I3dMouseSensor::ESpeed speedSetting = i3dmouseParam.GetSpeed();
	 // See "Programming for the 3D Mouse", Section 5.1.3	"3D 마우스 프로그래밍", 5.1.3 절 참조
	float speed = (speedSetting == I3dMouseSensor::kLowSpeed ? 0.25f : speedSetting == I3dMouseSensor::kHighSpeed ?  4.f : 1.f);

	 // Multiplying by the following will convert the 3d mouse data to real world units	다음을 곱하면 3D 마우스 데이터가 실제 단위로 변환됩니다.
	mouseData2PanZoom *= speed;
	mouseData2Rotation *= speed;

	std::map<HANDLE, TInputData>::iterator iterator=fDevice2Data.begin();
	while (iterator != fDevice2Data.end()) {

		// If we have not received data for a while send a zero event	잠시 동안 데이터를받지 못하면 0 이벤트를 보냅니다.
		if ((--(iterator->second.fTimeToLive)) == 0) {
			iterator->second.fAxes.assign(6, .0);
		} else if (/*!t_bPoll3dmouse &&*/ !iterator->second.fIsDirty) {
		  // If we are not polling then only handle the data that was actually received	폴링하지 않으면 실제로 수신 된 데이터 만 처리합니다.
			++iterator;
			continue;
		}
		iterator->second.fIsDirty=false;

		// get a copy of the device	장치 사본을 얻습니다.
		HANDLE hdevice = iterator->first;

		// get a copy of the motion vectors and apply the user filters	모션 벡터의 사본을 얻고 사용자 필터를 적용합니다.
		std::vector<float> motionData = iterator->second.fAxes;

		// apply the user filters	사용자 필터 적용

		// Pan Zoom filter	팬 확대 / 축소 필터
		// See "Programming for the 3D Mouse", Section 5.1.2	"3D 마우스 프로그래밍", 5.1.2 절 참조
		if (!i3dmouseParam.IsPanZoom()) {
			// Pan zoom is switched off so set the translation vector values to zero	팬 줌이 해제되어 번역 벡터 값을 0으로 설정합니다.
			motionData[0] =  motionData[1] =  motionData[2] = 0.;
		}

		// Rotate filter	필터를 회전합니다.
		// See "Programming for the 3D Mouse", Section 5.1.1
		if (!i3dmouseParam.IsRotate()) {
			// Rotate is switched off so set the rotation vector values to zero	회전이 꺼 지므로 회전 벡터 값을 0으로 설정합니다.
			motionData[3] =  motionData[4] =  motionData[5] = 0.;
		}

		// convert the translation vector into physical data	번역 벡터를 실제 데이터로 변환합니다.
		for (int axis = 0; axis < 3; axis++) {
			 motionData[axis] *= mouseData2PanZoom;
		 }
		// convert the directed Rotate vector into physical data	방향 지정된 회전 벡터를 물리적 데이터로 변환합니다.
		// See "Programming for the 3D Mouse", Section 7.2.2
		for (int axis = 3; axis < 6; axis++) {
			motionData[axis] *= mouseData2Rotation;
		}

		// Now that the data has had the filters and sensitivty settings applied
		// calculate the displacements since the last view update

/*
		// 데이터에 필터 및 민감도 설정이 적용되었으므로
		// 마지막 뷰 업데이트 이후의 변위를 계산합니다.
*/

		for (int axis = 0; axis < 6; axis++) {
			motionData[axis] *= dwElapsedTime;
		}


		// Now a bit of book keeping before passing on the data	이제 데이터를 전달하기 전에 약간의 책을 보관합니다.
		if (iterator->second.IsZero()) {
			iterator = fDevice2Data.erase(iterator);
		} else {
			++iterator;
		}

		// Work out which will be the next device	다음 장치가 될 워크 아웃
		HANDLE hNextDevice = 0;
		if (iterator != fDevice2Data.end()) {
			hNextDevice = iterator->first;
		}

		 // Pass the 3dmouse input to the view controller	3dmouse 입력을 뷰 컨트롤러로 전달합니다.
		 Move3d(hdevice, motionData);

		// Because we don't know what happened in the previous call, the cache might have
		// changed so reload the iterator

/*
		// 이전 호출에서 어떤 일이 발생했는지 모르기 때문에 캐시에
		// 변경하여 반복기를 다시로드하십시오.
*/

		iterator = fDevice2Data.find(hNextDevice);
   }

	if (!fDevice2Data.empty()) {
		fLast3dmouseInputTime = dwNow;
	} else {
		fLast3dmouseInputTime = 0;
	}
}

/*!
	Called when new raw input data is available
*/

/*
	새로운 원시 입력 데이터를 사용할 수있을 때 호출됩니다.
*/

void Mouse3DInput::OnRawInput(UINT nInputCode, HRAWINPUT hRawInput)
{
	const size_t cbSizeOfBuffer=1024;
	BYTE pBuffer[cbSizeOfBuffer];

	PRAWINPUT pRawInput = reinterpret_cast<PRAWINPUT>(pBuffer);
	UINT cbSize = cbSizeOfBuffer;

	if (::GetRawInputData(hRawInput, RID_INPUT, pRawInput, &cbSize, sizeof(RAWINPUTHEADER)) == static_cast<UINT>(-1)) {
		return;
	}

	bool b3dmouseInput = TranslateRawInputData(nInputCode, pRawInput);
	::DefRawInputProc(&pRawInput, 1, sizeof(RAWINPUTHEADER));

	// Check for any buffered messages	버퍼링 된 메시지를 확인합니다.
	cbSize = cbSizeOfBuffer;
	UINT nCount = this->GetRawInputBuffer(pRawInput, &cbSize, sizeof(RAWINPUTHEADER));
	if (nCount == (UINT)-1) {
        QLOG_DEBUG() << "GetRawInputBuffer returned error" << GetLastError() << "\n";
	}

	while (nCount>0 && nCount !=  static_cast<UINT>(-1)) {
		PRAWINPUT pri = pRawInput;
		UINT nInput;
		for (nInput=0; nInput<nCount; ++nInput) {
			b3dmouseInput |= TranslateRawInputData(nInputCode, pri);
			// clean the buffer	버퍼를 지운다.
			::DefRawInputProc(&pri, 1, sizeof(RAWINPUTHEADER));

			pri = NEXTRAWINPUTBLOCK(pri);
		}
		cbSize = cbSizeOfBuffer;
		nCount = this->GetRawInputBuffer(pRawInput, &cbSize, sizeof(RAWINPUTHEADER));
	}

	// If we have mouse input data for the app then tell tha app about it	앱에 대한 마우스 입력 데이터가있는 경우 app에 알립니다.

	if (b3dmouseInput) {
		On3dmouseInput();
	}
}



bool Mouse3DInput::TranslateRawInputData(UINT nInputCode, PRAWINPUT pRawInput)
{
	bool bIsForeground = (nInputCode == RIM_INPUT);

#if _TRACE_RI_TYPE
    QLOG_DEBUG() << "Rawinput.header.dwType=0x%x\n", pRawInput->header.dwType;
#endif
	// We are not interested in keyboard or mouse data received via raw input	원시 입력을 통해 수신 된 키보드 또는 마우스 데이터에 관심이 없습니다.
	if (pRawInput->header.dwType != RIM_TYPEHID) return false;

#if _TRACE_RIDI_DEVICENAME
	UINT dwSize=0;
	if (::GetRawInputDeviceInfo(pRawInput->header.hDevice, RIDI_DEVICENAME, NULL, &dwSize) == 0)  {
		std::vector<wchar_t> szDeviceName(dwSize+1);
		if (::GetRawInputDeviceInfo(pRawInput->header.hDevice, RIDI_DEVICENAME, &szDeviceName[0],	&dwSize) >0) {
            QLOG_TRACE() << "Device Name = %s\nDevice handle = 0x%x\n", &szDeviceName[0], pRawInput->header.hDevice;
		}
   }
#endif

	RID_DEVICE_INFO sRidDeviceInfo;
	sRidDeviceInfo.cbSize = sizeof(RID_DEVICE_INFO);
	UINT cbSize = sizeof(RID_DEVICE_INFO);

	if (::GetRawInputDeviceInfo(pRawInput->header.hDevice, RIDI_DEVICEINFO, &sRidDeviceInfo, &cbSize) == cbSize) {
#if _TRACE_RIDI_DEVICEINFO
		switch (sRidDeviceInfo.dwType)  {
			case RIM_TYPEMOUSE:
                QLOG_DEBUG() << "\tsRidDeviceInfo.dwType=RIM_TYPEMOUSE\n";
				break;
			case RIM_TYPEKEYBOARD:
                QLOG_DEBUG() << "\tsRidDeviceInfo.dwType=RIM_TYPEKEYBOARD\n";
				break;
			case RIM_TYPEHID:
                QLOG_DEBUG() <<"\tsRidDeviceInfo.dwType=RIM_TYPEHID\n";
                QLOG_DEBUG() <<"\tVendor=0x%x\n\tProduct=0x%x\n\tUsagePage=0x%x\n\tUsage=0x%x\n",
						sRidDeviceInfo.hid.dwVendorId,
						sRidDeviceInfo.hid.dwProductId,
						sRidDeviceInfo.hid.usUsagePage,
						sRidDeviceInfo.hid.usUsage);
				break;
		}
#endif

		if (sRidDeviceInfo.hid.dwVendorId == LOGITECH_VENDOR_ID) {
			if (pRawInput->data.hid.bRawData[0] == 0x01) { // Translation vector	번역 벡터

				TInputData& deviceData = fDevice2Data[pRawInput->header.hDevice];
				deviceData.fTimeToLive = kTimeToLive;
				if (bIsForeground) {
					short* pnRawData = reinterpret_cast<short*>(&pRawInput->data.hid.bRawData[1]);
					// Cache the pan zoom data	팬 확대 / 축소 데이터 캐시
					deviceData.fAxes[0] = static_cast<float>(pnRawData[0]);
					deviceData.fAxes[1] = static_cast<float>(pnRawData[1]);
					deviceData.fAxes[2] = static_cast<float>(pnRawData[2]);

#if _TRACE_RI_RAWDATA
                    QLOG_DEBUG() <<"Pan/Zoom RI Data =\t0x%x,\t0x%x,\t0x%x\n",
                                    pnRawData[0],  pnRawData[1],  pnRawData[2];
#endif
					if (pRawInput->data.hid.dwSizeHid >= 13) {// Highspeed package	고속 패키지
						// Cache the rotation data	회전 데이터를 캐시하십시오.
						deviceData.fAxes[3] = static_cast<float>(pnRawData[3]);
						deviceData.fAxes[4] = static_cast<float>(pnRawData[4]);
						deviceData.fAxes[5] = static_cast<float>(pnRawData[5]);
						deviceData.fIsDirty = true;
#if _TRACE_RI_RAWDATA
                        QLOG_DEBUG() <<"Rotation RI Data =\t0x%x,\t0x%x,\t0x%x\n",
                             pnRawData[3], pnRawData[4], pnRawData[5];
#endif
						return true;
					}
				} else { // Zero out the data if the app is not in forground	앱이 forground에 없으면 데이터를 0으로 만듭니다.
					deviceData.fAxes.assign(6, 0.f);
				}
			} else if (pRawInput->data.hid.bRawData[0] == 0x02) { // Rotation vector
				// If we are not in foreground do nothing
				// The rotation vector was zeroed out with the translation vector in the previous message

/*
				// 우리가 전경에 없다면 아무것도하지 않는다.
				// 이전 메시지의 이동 벡터로 회전 벡터가 제로화되었습니다.
*/

				if (bIsForeground) {
					TInputData& deviceData = fDevice2Data[pRawInput->header.hDevice];
					deviceData.fTimeToLive = kTimeToLive;

					short* pnRawData = reinterpret_cast<short*>(&pRawInput->data.hid.bRawData[1]);
					// Cache the rotation data	회전 데이터를 캐시하십시오.
					deviceData.fAxes[3] = static_cast<float>(pnRawData[0]);
					deviceData.fAxes[4] = static_cast<float>(pnRawData[1]);
					deviceData.fAxes[5] = static_cast<float>(pnRawData[2]);
					deviceData.fIsDirty = true;

#if _TRACE_RI_RAWDATA
                    QLOG_DEBUG() <<"Rotation RI Data =\t0x%x,\t0x%x,\t0x%x\n",
                        pnRawData[0],  pnRawData[1], pnRawData[2];
#endif
					return true;
				}
			} else if (pRawInput->data.hid.bRawData[0] == 0x03)  { // Keystate change
				// this is a package that contains 3d mouse keystate information
				// bit0=key1, bit=key2 etc.

/*
				// 이것은 3D 마우스 키스톤 정보가 들어있는 패키지입니다.
				// bit0 = key1, bit = key2 등
*/



				unsigned long dwKeystate = *reinterpret_cast<unsigned long*>(&pRawInput->data.hid.bRawData[1]);
#if _TRACE_RI_RAWDATA
                QLOG_DEBUG() <<"ButtonData =0x%x\n", dwKeystate;
#endif
				// Log the keystate changes	키스톤 변경 사항을 기록하십시오.
				unsigned long dwOldKeystate = fDevice2Keystate[pRawInput->header.hDevice];
				if (dwKeystate != 0) {
					fDevice2Keystate[pRawInput->header.hDevice] = dwKeystate;
				} else {
					fDevice2Keystate.erase(pRawInput->header.hDevice);
				}

				//  Only call the keystate change handlers if the app is in foreground	앱이 포 그라운드에있는 경우에만 키스톤 변경 핸들러를 호출합니다.
				if (bIsForeground) {
					unsigned long dwChange = dwKeystate ^ dwOldKeystate;


					for (int nKeycode=1; nKeycode<33; nKeycode++) {
						if (dwChange & 0x01) {
							int nVirtualKeyCode = HidToVirtualKey(sRidDeviceInfo.hid.dwProductId, nKeycode);
							if (nVirtualKeyCode) {
								if (dwKeystate&0x01) {
									On3dmouseKeyDown(pRawInput->header.hDevice, nVirtualKeyCode);
								} else {
									On3dmouseKeyUp(pRawInput->header.hDevice, nVirtualKeyCode);
								}
							}
						}
						dwChange >>=1;
						dwKeystate >>=1;
					}
				}
			}
		}
   }
   return false;
}
