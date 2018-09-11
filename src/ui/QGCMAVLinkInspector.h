#ifndef QGCMAVLINKINSPECTOR_H
#define QGCMAVLINKINSPECTOR_H

#include <QWidget>
#include <QMap>
#include <QTimer>

#include "MAVLinkProtocol.h"

namespace Ui {
    class QGCMAVLinkInspector;
}

class QTreeWidgetItem;
class UASInterface;

class QGCMAVLinkInspector : public QWidget
{
    Q_OBJECT

public:
    explicit QGCMAVLinkInspector(MAVLinkProtocol* protocol, QWidget *parent = 0);
    ~QGCMAVLinkInspector();

public slots:
    void receiveMessage(LinkInterface* link,mavlink_message_t message);
    /** @brief Clear all messages */
    /** 모든 메시지 지우기 */
    void clearView();
    /** @brief Update view */
    /** 업데이트보기 */
    void refreshView();
    /** @brief Add system to the list */
    /** brief 목록에 시스템 추가 */
    void addSystem(UASInterface* uas);
    /** @brief Add component to the list */
    /** brief 목록에 구성 요소 추가 */
    void addComponent(int uas, int component, const QString& name);
    /** @Brief Select a system through the drop down menu */
    /**  @Brief 드롭 다운 메뉴를 통해 시스템 선택 */
    void selectDropDownMenuSystem(int dropdownid);
    /** @Brief Select a component through the drop down menu */
    /** @Brief 드롭 다운 메뉴에서 구성 요소 선택 */
    void selectDropDownMenuComponent(int dropdownid);

    void rateTreeItemChanged(QTreeWidgetItem* paramItem, int column);

protected:
    MAVLinkProtocol *_protocol;     ///< MAVLink instance
                                    /// <MAVLink 인스턴스
    int selectedSystemID;           ///< Currently selected system
                                    /// <현재 선택된 시스템
    int selectedComponentID;        ///< Currently selected component
                                    /// <현재 선택된 구성 요소
    QMap<int, int> systems;         ///< Already observed systems
                                    /// <이미 관측 된 시스템
    QMap<int, int> components;      ///< Already observed components
                                    /// <이미 관찰 된 구성 요소
    QMap<int, float> onboardMessageInterval; ///< Stores the onboard selected data rate
                                             /// <온보드 선택한 데이터 속도를 저장합니다.
    QMap<int, QTreeWidgetItem*> rateTreeWidgetItems; ///< Available rate tree widget items
                                                     /// <사용 가능한 비율 트리 위젯 항목
    QTimer updateTimer; ///< Only update at 1 Hz to not overload the GUI
                        /// <GUI를 과부하시키지 않으려면 1Hz로만 업데이트하십시오
    QHash<quint32, mavlink_message_info_t> messageInfo; ///< Meta information about all messages
                                                        /// 모든 메시지에 대한 메타 정보
 
    QMap<int, QTreeWidgetItem* > uasTreeWidgetItems; ///< Tree of available uas with their widget
                                                     /// <위젯과 함께 사용 가능한 uas 트리
    QMap<int, QMap<int, QTreeWidgetItem*>* > uasMsgTreeItems; ///< Stores the widget of the received message for each UAS
                                                              /// <각 UAS에 대해받은 메시지의 위젯을 저장합니다.

    QMap<int, mavlink_message_t* > uasMessageStorage; ///< Stores the messages for every UAS
                                                      /// <모든 UAS에 대한 메시지를 저장합니다.

    QMap<int, QMap<int, float>* > uasMessageHz; ///< Stores the frequency of each message of each UAS
                                                /// <각 UAS의 각 메시지의 빈도를 저장합니다.
    QMap<int, QMap<int, unsigned int>* > uasMessageCount; ///< Stores the message count of each message of each UAS
                                                          /// <각 UAS의 각 메시지의 메시지 수를 저장합니다.

    QMap<int, QMap<int, quint64>* > uasLastMessageUpdate; ///< Stores the time of the last message for each message of each UAS
                                                          /// <각 UAS의 각 메시지에 대한 마지막 메시지의 시간을 저장합니다.

    /* @brief Update one message field */
    /*@brief 하나의 메시지 필드 업데이트 */
    void updateField(int sysid, int msgid, int fieldid, QTreeWidgetItem* item);
    /** @brief Rebuild the list of components */
    /** brief 구성 요소 목록을 다시 작성합니다. */
    void rebuildComponentList();
    /** @brief Change the stream interval */
    /** @brief 스트림 간격 변경 */
    void changeStreamInterval(int msgid, int interval);
    /* @brief Create a new tree for a new UAS */
    /** @brief 새로운 UAS를위한 새로운 트리 만들기 */
    void addUAStoTree(int sysId);

    static const unsigned int updateInterval; ///< The update interval of the refresh function
                                              /// <새로 고침 함수의 업데이트 간격
    static const float updateHzLowpass; ///< The low-pass filter value for the frequency of each message
                                        /// 각 메시지의 빈도에 대한 로우 패스 필터 값


private:
    Ui::QGCMAVLinkInspector *ui;
};

#endif // QGCMAVLINKINSPECTOR_H
