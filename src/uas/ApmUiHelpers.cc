
#include "ApmUiHelpers.h"
#include "ArduPilotMegaMAV.h"

void ApmUiHelpers::addRoverModes(QComboBox* comboBox)
{
    comboBox->clear();
    for (int count = 0; count < Rover::LAST_MODE; count++){
        ModeMessage modeMsg(0, 0, count, 0, 0);
        QString modeStr = Rover::MessageFormatter::format(modeMsg);
        if (!(modeStr.contains("Unknown", Qt::CaseInsensitive)
              || modeStr.contains("Reserved", Qt::CaseInsensitive))){
            // If mode valid add it and mode Id to comboBox
            // 유효한 모드가 comboBox에 해당 모드 및 모드 ID를 추가하는 경우
            comboBox->addItem(modeStr, count);
        }
    }
}

void ApmUiHelpers::addPlaneModes(QComboBox* comboBox)
{
    comboBox->clear();
    for (int count = 0; count < Plane::LAST_MODE; count++){
        ModeMessage modeMsg(0, 0, count, 0, 0);
        QString modeStr = Plane::MessageFormatter::format(modeMsg);
        if (!(modeStr.contains("Unknown", Qt::CaseInsensitive)
              ||(modeStr.contains("Reserved", Qt::CaseInsensitive)))){
            // If mode valid add it and mode Id to comboBox
            // 유효한 모드가 comboBox에 해당 모드 및 모드 ID를 추가하는 경우
            comboBox->addItem(modeStr, count);
        }
    }
}

void ApmUiHelpers::addCopterModes(QComboBox* comboBox)
{
    comboBox->clear();
    for (int count = 0; count < Copter::LAST_MODE; count++){
        ModeMessage modeMsg(0, 0, count, 0, 0);
        QString modeStr = Copter::MessageFormatter::format(modeMsg);
        if (!(modeStr.contains("Unknown", Qt::CaseInsensitive)
              ||(modeStr.contains("Reserved", Qt::CaseInsensitive)))){
            // If mode valid add it and mode Id to comboBox
            // 유효한 모드가 comboBox에 해당 모드 및 모드 ID를 추가하는 경우
            comboBox->addItem(modeStr, count);
        }
    }
}
