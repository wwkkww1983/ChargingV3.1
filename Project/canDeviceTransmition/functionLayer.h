#pragma once
/*******************
//description：函数层，函数集合。
//
//author： chenlin
//date：20180923
*/

#include "Common.h"
#include "../common/common.h"
#include "Protocol.h"
#include "Transmit.h" 
#define GET_T CTransmit::GetInstance()
#define GET_P CProtocol::GetInstance()
#include <string>
#include <vector>

#define VT_STR std::vector<std::string>&


//打开CAN设备
bool openCAN(char * resultString);

//关闭CAN设备
void closeCAN(char * resultString);

//读写CAN ID
bool readOrWriteCANID(VT_STR vtStrCommand, char* resultString);

//认证设备
bool verifyDevice(VT_STR vtStrCommand, char* resultString);

//认证设备
bool readOrWriteBeginMode(VT_STR vtStrCommand, char* resultString);


//读取电池信息动态 
bool readDanyBatteryInfo(VT_STR vtStrCommand, char* resultString);


//读取/写入充电状态
bool readOrWriteChargingState(VT_STR vtStrCommand, char* resultString);
 

//读取/写入放电状态
bool readOrWriteDisChargeState(VT_STR vtStrCommand, char* resultString);

//读取/写入放电状态
bool writeAutoDischargeDay(VT_STR vtStrCommand, char* resultString);

//读取电池信息静态 
bool readStaticBatteryInfo(VT_STR vtStrCommand, char* resultString);