/*=====================================================================

QGroundControl Open Source Ground Control Station

(c) 2009, 2010 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>

This file is part of the QGROUNDCONTROL project

    QGROUNDCONTROL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QGROUNDCONTROL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

#ifndef PARAMETERLIST_H
#define PARAMETERLIST_H

#include <QMap>
#include <QVector>
#include <QIODevice>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QtXml>
#include <QStringList>

#include "mavlink_types.h"
#include "QGCParamID.h"
#include "Parameter.h"
#include "OpalRT.h"

namespace OpalRT
{
class ParameterList
{
public:

    class const_iterator
    {
        friend class ParameterList;

    public:
        inline const_iterator() {}
        const_iterator(const const_iterator& other);

        const_iterator& operator+=(int i) {
            index += i;
            return *this;
        }
        bool operator<(const const_iterator& other) const {
            return (this->paramList == other.paramList)
                   &&(this->index<other.index);
        }
        bool operator==(const const_iterator& other) const {
            return (this->paramList == other.paramList)
                   &&(this->index==other.index);
        }
        bool operator!=(const const_iterator& other) const {
            return !((*this) == other);
        }
        const Parameter& operator*() const {
            return paramList[index];
        }
        const Parameter* operator->() const {
            return &paramList[index];
        }

        const_iterator& operator++() {
            ++index;
            return *this;
        }
    private:
        const_iterator(QList<Parameter>);
        QList<Parameter> paramList;
        int index;
    };


    ParameterList();
    ~ParameterList();

    /** Count the number of parameters in the list.
      \return Total number of parameters
      */
    /** 목록에있는 매개 변수의 수를 센다.
      \ return 총 매개 변수 수
      */
    int count();

    /** Find p in the list and return its index.
      \note In order to use this index to look up p, the component is also needed.
      \return the index of p or -1 if p is not found
      \example
      \code
      int compid = OpalRT::CONTROLLER_ID;
      Parameter p("simulinkpath", "simulinkparamname", compid, QGCParamID("PID_GAIN"));
      ParameterList pList;
      if ((int index=pList.indexOf(p)) != -1)
         QLOG_DEBUG() << "PID_GAIN is at index " << index;
      \endcode
      */
    /** 목록에서 p를 찾아 색인을 반환합니다.
      \ note이 색인을 사용하여 p를 찾으려면 구성 요소도 필요합니다.
      \ p의 인덱스를 반환하거나 p가 없으면 -1을 반환합니다.
      \예
      \암호
      int compid = OpalRT :: CONTROLLER_ID;
      매개 변수 p ( "simulinkpath", "simulinkparamname", compid, QGCParamID ( "PID_GAIN"));
      ParameterList pList;
      if ((int index = pList.indexOf (p))! = -1)
         QLOG_DEBUG () << "PID_GAIN이 인덱스에 있습니다"<< index;
      \ endcode
      */
    int indexOf(const Parameter& p);
    bool contains(int compid, QGCParamID paramid) const {
        return (*params)[compid].contains(paramid);
    }

    /// Get a parameter from the list
    /// 목록에서 매개 변수 가져 오기
    const Parameter getParameter(int compid, QGCParamID paramid) const {
        return (*params)[compid][paramid];
    }
    Parameter& getParameter(int compid, QGCParamID paramid) {
        return (*params)[compid][paramid];
    }
    const Parameter getParameter(int compid, int index) const {
        return *((*paramList)[compid][index]);
    }

    /** Convenient syntax for calling OpalRT::Parameter::getParameter() */
    /** OpalRT :: Parameter :: getParameter () 호출을위한 편리한 문법 */
    Parameter& operator()(int compid, QGCParamID paramid) {
        return getParameter(compid, paramid);
    }
    Parameter& operator()(uint8_t compid, QGCParamID paramid) {
        return getParameter(static_cast<int>(compid), paramid);
    }

    const_iterator begin() const;
    const_iterator end() const;

protected:
    /** Store the parameters mapped by componentid, and paramid.
       \code
       // Look up a parameter
       int compid = 1;
       QGCParamID paramid("PID_GAIN");
       Parameter p = params[compid][paramid];
       \endcode
       */
    /** componentid와 paramid가 매핑 한 매개 변수를 저장합니다.
       \암호
       // 매개 변수를 찾습니다.
       int compid = 1;
       QGCParamID paramid ( "PID_GAIN");
       매개 변수 p = params [compid] [paramid];
       \ endcode
       */
    QMap<int, QMap<QGCParamID, Parameter> > *params;
    /**
      Store pointers to the parameters to allow fast lookup by index.
      This variable may be changed to const pointers to ensure all changes
      are made through the map container.
      */
    /**
      포인터를 매개 변수에 저장하여 색인별로 빨리 조회 할 수 있습니다.
      이 변수는 모든 변경을 보장하기 위해 const 포인터로 변경 될 수 있습니다.
      지도 컨테이너를 통해 이루어집니다.
      */
    QList<QList<Parameter*> > *paramList;
    /**
      List of parameters which are necessary to control the servos.
      */
    /**
      서보를 제어하는 ​​데 필요한 매개 변수 목록입니다.
      */
    QStringList *reqdServoParams;
    /**
      Get the list of available parameters from Opal-RT.
      \param[out] opalParams Map of parameter paths/names to ids which are valid in Opal-RT
      */
    /**
      Opal-RT에서 사용 가능한 매개 변수 목록을 가져옵니다.
      \ param [out] opalParams Opal-RT에서 유효한 매개 변수 경로 / 이름의 ID에 대한 맵
      */
    void getParameterList(QMap<QString, unsigned short>* opalParams);

    /**
      Open a file for reading in the xml config data
      */
    /**
      xml 구성 데이터에서 읽을 파일 열기
      */
    bool open(QString filename=QString());
    /**
      Attempt to read XML configuration data from device
      \param[in] the device to read the xml data from
      \return true if the configuration was read successfully, false otherwise
      */
    /**
      장치에서 XML 구성 데이터를 읽으려고합니다.
      \ param [in] xml 데이터를 읽을 장치
      \ 구성을 성공적으로 읽었 으면 true를 반환하고 그렇지 않으면 false를 반환합니다.
      */
    bool read(QIODevice *device);

    void parseBlock(const QDomElement &block);
};
}
#endif // PARAMETERLIST_H
