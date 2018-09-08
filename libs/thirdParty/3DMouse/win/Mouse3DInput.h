#ifndef T3DMOUSE_INPUT_H
#define T3DMOUSE_INPUT_H

#include "MouseParameters.h"

#include <QWidget>
#include <vector>
#include <map>

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501  //target at least windows XP	 적어도 윈도우즈 XP를 목표로 삼는다.
#endif

#include <windows.h>


/*
	A class for connecting to and receiving data from a 3D Connexion 3D mouse

	This helper class manages the connection to a 3D mouse,  collecting WM_INPUT
	messages from Windows and converting the data into 3D motion data.

	This class is based on the SDK from 3D Connexion but is modified to work with Qt.

	It is Windows only since it uses the WM_INPUT messages from windows directly
	rather than Qt events.

	Note that it needs to be compiled with _WIN32_WINNT defined as 0x0501 (windows XP)
	or later because the raw input API was added in Windows XP. This also means that
	Qt needs to be compiled with this enabled otherwise the QEventDispatcherWin32 blocks
	in processEvents because the raw input messages do not cause the thread to be woken if
	Qt is compiled for Win 2000 targets.
*/

/*
	3D Connexion 3D 마우스에서 데이터를주고받는 클래스
	이 도우미 클래스는 3D 마우스 연결을 관리하고 WM_INPUT을 수집합니다.
	Windows에서 온 메시지를 3D 모션 데이터로 변환합니다.
	이 클래스는 3D Connexion의 SDK를 기반으로하지만 Qt에서 작동하도록 수정되었습니다.
	창에서 WM_INPUT 메시지를 직접 사용하기 때문에 Windows에서만 사용할 수 있습니다.
	Qt 이벤트보다는
	0x0501로 정의 된 _WIN32_WINNT (Windows XP)로 컴파일해야합니다.
	또는 나중에 Windows XP에서 원시 입력 API가 추가 되었기 때문입니다. 이것은 또한
	Qt를 컴파일해야합니다. 그렇지 않으면 QEventDispatcherWin32 블록이 활성화됩니다.
	원시 입력 메시지로 인해 스레드가 깨어나지 않으므로 processEvents에서
	Qt는 Win 2000 타겟 용으로 컴파일됩니다.
*/


class Mouse3DInput : public QObject
{
	Q_OBJECT
public:
		Mouse3DInput(QWidget* widget);
		~Mouse3DInput();

static	bool		Is3dmouseAttached();

		I3dMouseParam&			MouseParams();
		const I3dMouseParam&	MouseParams() const;

virtual	void		Move3d(HANDLE device, std::vector<float>& motionData);
virtual void		On3dmouseKeyDown(HANDLE device, int virtualKeyCode);
virtual void		On3dmouseKeyUp(HANDLE device, int virtualKeyCode);

signals:

		void		Move3d(std::vector<float>& motionData);
		void		On3dmouseKeyDown(int virtualKeyCode);
		void		On3dmouseKeyUp(int virtualKeyCode);

private:

		bool		InitializeRawInput(HWND hwndTarget);

static	bool		RawInputEventFilter(void* msg, long* result);

		void		OnRawInput(UINT nInputCode, HRAWINPUT hRawInput);
		UINT		GetRawInputBuffer(PRAWINPUT pData, PUINT pcbSize, UINT cbSizeHeader);
		bool		TranslateRawInputData(UINT nInputCode, PRAWINPUT pRawInput);
		void		On3dmouseInput();

		class TInputData
		{
		public:
		   TInputData() : fAxes(6) {}

		   bool IsZero() {
			  return (0.==fAxes[0] && 0.==fAxes[1] && 0.==fAxes[2] &&
				 0.==fAxes[3] && 0.==fAxes[4] && 0.==fAxes[5]);
		   }

		   int                   fTimeToLive; // For telling if the device was unplugged while sending data	데이터를 보내는 동안 기기가 분리되었는지 알려주기 위해
		   bool                  fIsDirty;
		   std::vector<float>	 fAxes;

		};

		HWND								fWindow;

		// Data cache to handle multiple rawinput devices	여러 rawinput 장치를 처리하기위한 데이터 캐시
		std::map< HANDLE, TInputData>       fDevice2Data;
		std::map< HANDLE, unsigned long>    fDevice2Keystate;

		// 3dmouse parameters	3dmouse 매개 변수
		MouseParameters						f3dMouseParams;     // Rotate, Pan Zoom etc.	회전, 팬 확대 / 축소 등

		// use to calculate distance traveled since last event	마지막 이벤트 이후로 이동 한 거리를 계산하는 데 사용합니다.
		DWORD								fLast3dmouseInputTime;

};

#endif
