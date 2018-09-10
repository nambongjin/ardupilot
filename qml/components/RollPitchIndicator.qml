//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//    (c) 2014 Author: Bill Bonney <billbonney@communistech.com>
//

import QtQuick 2.0

Item {
    id: rootRollPitchIndicator
    property real rollAngle : 0
    property real pitchAngle: 0
    property bool enableBackgroundVideo: false
    height: parent.height
    width: parent.width
    anchors.fill: parent

    Item { // Artificial Horizon     인공 지평
        id: artificialHorizonBackground
        height: parent.width
        width: parent.height
        anchors.fill: parent

        Rectangle { // Blue Sky  푸른 하늘
                id: blueSky
                color: "skyblue"
                smooth: true
                anchors.centerIn: parent
                height: parent.height * 4.0
                width: parent.width * 4.0

                //So we can pitch and roll the rectangle with no white background shown
                //scale: parent.scale * 4.0

                /*
                // 흰색 배경이없는 사각형을 피치 롤을 할 수 있습니다.
                // scale : parent.scale * 4.0
                */


                visible: !enableBackgroundVideo
        }


        Rectangle { // Ground    그라운드
                id: ground
                height: parent.height * 2.0
                width: parent.width * 4.0

                anchors.left: blueSky.left
                anchors.right: blueSky.right
                anchors.bottom: blueSky.bottom

                color: "#038000"
                smooth: true

                visible: !enableBackgroundVideo
        }

        Rectangle {
                id: videoImage // Just for testing   테스트 용입니다.
                anchors { fill: parent; centerIn: parent }
                color: "darkgrey"
                visible: enableBackgroundVideo
        }

         transformOrigin: Item.Center

        //Up and down pitch  위아래 피치
        transform: Translate {y: pitchAngle * 1.75}

        //Left and Right Roll    왼쪽 및 오른쪽 롤
        rotation: -rollAngle

    } // End Artficial Horizon   Artficial Horizon 끝내기

    Item { //Roll Indicator  롤 표시기

        id: rollIndicator
        width: parent.width
        height: parent.height/2
        scale: parent.scale * 0.7
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter

        z: 1

        Image { // Roll Graticule    롤 계수기
            id: rollGraticule
            source: "../resources/components/rollPitchIndicator/rollGraticule.svg"

            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            transformOrigin: Image.Bottom
            fillMode: Image.PreserveAspectFit
            smooth: true
            rotation: -rollAngle

            Image {
                source: "../resources/components/rollPitchIndicator/rollPointer.svg"
                fillMode: Image.PreserveAspectFit
                transformOrigin: Item.Bottom
                rotation: rollAngle
            }
          }//Roll Graticule  격자 계수 롤
       }//Roll Indicator     롤 표시기


    Image { // Cross Hairs
        id: crossHairs
        anchors.centerIn: parent
        z:3
        source: "../resources/components/rollPitchIndicator/crossHair.svg"

    }
    states: [
        State {
            name: "State1"
        }
    ]
}
