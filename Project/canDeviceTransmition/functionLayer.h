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
void openCAN(char * resultString);

//关闭CAN设备
void closeCAN(char * resultString);

bool readOrWriteCANID(VT_STR vtStrCommand, char* resultString);

