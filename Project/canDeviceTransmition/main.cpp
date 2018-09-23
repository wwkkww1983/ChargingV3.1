// TransmitionTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include "Common.h"
#include "../common/common.h" 
#include "functionLayer.h"
#include <cstdlib>  
static char rbuf[256] = "";
static char wbuf[MAX_BUF_SIZE] = "";
HANDLE hPipe = 0;	DWORD wlen = 0;	DWORD rlen = 0;

void displayOption(){
	printf("\n请输入指令: \n\t0 退出\t1 打开can设备\t2 读取canid指令\
		   \n\t3 设置canid指令\t4 认证\t5 读取起始模式\
		   \n\t6 读取最大充电数\t7 读取充电开关\t8 读取版本信息\
		   \n\t9 读取总静态数据\t10 读取动态数据\t11 读取放电开关\
		   \n");
}
void sendToClint()
{
	printf("向有名管道句柄%d，发送:%s",hPipe, wbuf);
	WriteFile(hPipe, wbuf, MAX_BUF_SIZE, &wlen, 0);
	memset(wbuf, MAX_BUF_SIZE, 0);
}
//回调函数，打印操作结果
static void _callbackPrintf(int nType, bool bSend2Clint = true)
{
	if (nType == 1)
	{
		printf("%s\n", GET_P->getDebugData().c_str());
		sprintf_s(wbuf, MAX_BUF_SIZE, "%s,%d,%s\n", S2C, enCANDeviErrorCode::Success, GET_P->getDebugData().c_str());
	}
	if (nType == 2)
	{
		printf("%s\n", GET_T->getDebugData().c_str());
		if (bSend2Clint)
			sprintf_s(wbuf, MAX_BUF_SIZE, "%s,%d,%s\n", S2C, enCANDeviErrorCode::DetailError, GET_T->getDebugData().c_str());
	}
	if (bSend2Clint)
	{
		//displayOption();
		sendToClint();
	}
}

//分割字符，参数1 原字符串（输入）， 参数2 分割字符（输入）， 参数3 字符串向量的引用（输出）
void split(std::string strtem, char a, VT_STR vtStrCommand)
{
	vtStrCommand.clear(); 
	std::string::size_type pos1, pos2;
	pos2 = strtem.find(a);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		vtStrCommand.push_back(strtem.substr(pos1, pos2 - pos1));
		pos1 = pos2 + 1;
		pos2 = strtem.find(a, pos1);
	}
	vtStrCommand.push_back(strtem.substr(pos1));
}


void readCanId()
{
	stCAN_DevData dataObj;
	GET_P->getCommandReadCanId(dataObj);
	GET_T->sendCanData(dataObj, Uint8ToUint16(g_CAN_ID_Common));
}

void writeCanId()
{
	stCAN_DevData dataObj;
	GET_P->getCommandWriteCanId(dataObj, g_CAN_ID_Default);
	GET_T->sendCanData(dataObj, Uint8ToUint16(g_CAN_ID_Common));
}

void sendVerify()
{
	stCAN_DevData dataObj;
	GET_P->getCommandVerify(dataObj);
	UINT canID = Uint8ToUint16(g_CAN_ID_Default); 
	canID |= 0x400;   //v1.3can id需要或上0x400
	GET_T->sendCanData(dataObj, canID);
}


void readBeginMode()
{
	stCAN_DevData dataObj;
	GET_P->getCommandBeginMode(dataObj);
	UINT canID = Uint8ToUint16(g_CAN_ID_Default);
	canID |= 0x400;   //v1.3can id需要或上0x400
	GET_T->sendCanData(dataObj, canID);
}

void readMaxCharge()
{
	stCAN_DevData dataObj;
	GET_P->getCommandMaxCharge(dataObj);
	UINT canID = Uint8ToUint16(g_CAN_ID_Default);
	canID |= 0x400;   //v1.3can id需要或上0x400
	GET_T->sendCanData(dataObj, canID);
}

void readOrWriteCharge()
{
	printf("请输入(0读取充电/1设置充电):\n");
	int nReadOrWrite = 0, chargeId = 0;
	stCAN_DevData dataObj;
	scanf_s("%d", &nReadOrWrite);
	switch (nReadOrWrite)
	{
	case 0:
		GET_P->getCommandCharge(dataObj, false, 0);
		break;
	case 1:
	{
			  printf("请输入充电号(1-15):");
			  scanf_s("%d", &chargeId);
			  if (chargeId>0 && chargeId <=15  )
			  {
				  GET_P->getCommandCharge(dataObj, true, chargeId);
				  break;
			  }
			  else
			  {
				  printf("错误输入\n"); 
				  displayOption();
				  return;
			  }

	}
	default:
		printf("未知输入\n");
		displayOption();
		return;
		break;
	}
	
	
	UINT canID = Uint8ToUint16(g_CAN_ID_Default);
	canID |= 0x400;   //v1.3can id需要或上0x400
	GET_T->sendCanData(dataObj, canID);
}

void readLoadAppInfo()
{
	stCAN_DevData dataObj;
	GET_P->getCommandLoadAppInfo(dataObj);
	UINT canID = Uint8ToUint16(g_CAN_ID_Default);
	canID |= 0x400;   //v1.3can id需要或上0x400
	GET_T->sendCanData(dataObj, canID);
}

void readStaticData()
{
	stCAN_DevData dataObj;
	GET_P->getCommandStaticData(dataObj);
	UINT canID = Uint8ToUint16(g_CAN_ID_Default);
	canID |= 0x400;   //v1.3can id需要或上0x400
	GET_T->sendCanData(dataObj, canID);
}

void readDynaData()
{
	stCAN_DevData dataObj;
	GET_P->getCommandDynaData(dataObj);
	UINT canID = Uint8ToUint16(g_CAN_ID_Default);
	canID |= 0x400;   //v1.3can id需要或上0x400
	GET_T->sendCanData(dataObj, canID);
}

void readOrWriteDisC()
{
	printf("请输入(0读取放电/1设置放电):\n");
	int nReadOrWrite = 0, chargeId = 0;
	stCAN_DevData dataObj;
	scanf_s("%d", &nReadOrWrite);
	switch (nReadOrWrite)
	{
	case 0:
		GET_P->getCommandDisCharge(dataObj, false, 0);
		break;
	case 1:
	{
			  printf("请输入放电号(1-15):");
			  scanf_s("%d", &chargeId);
			  if (chargeId > 0 && chargeId <= 15)
			  {
				  GET_P->getCommandDisCharge(dataObj, true, chargeId);
				  break;
			  }
			  else
			  {
				  printf("错误输入\n");
				  displayOption();
				  return;
			  }

	}
	default:
		printf("错误输入\n");
		displayOption();
		return;
		break;
	}

	UINT canID = Uint8ToUint16(g_CAN_ID_Default);
	canID |= 0x400;   //v1.3can id需要或上0x400
	GET_T->sendCanData(dataObj, canID); 
}

int _tmain(int argc, _TCHAR* argv[])
{
	//system("mode con cols=100 ");    //调整窗口大小
	GET_P->m_pPrintfFun = _callbackPrintf;
	GET_T->m_pPrintfFun = _callbackPrintf;	
	
	//创建管道
	hPipe = CreateNamedPipe(
		TEXT(PIPE_NAME),						//管道名
		PIPE_ACCESS_DUPLEX,									//管道类型 
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,	//管道参数，双向通信 
		PIPE_UNLIMITED_INSTANCES,							//管道能创建的最大实例数量
		0,													//输出缓冲区长度 0表示默认
		0,													//输入缓冲区长度 0表示默认
		NMPWAIT_WAIT_FOREVER,								//超时时间,NMPWAIT_WAIT_FOREVER为不限时等待
		NULL);
	if (INVALID_HANDLE_VALUE == hPipe)
	{
		printf("创建管道失败:%d ", GetLastError());
		system("PAUSE");
	}
	else{
		printf("创建管道完成，等待调用进程连接管道\n");
		//等待客户端连接管道
		ConnectNamedPipe(hPipe, NULL);
		printf("主进程接入管道\n");

		std::vector<std::string> vtStrCommand;
		
		while (true)
		{
			if (ReadFile(hPipe, rbuf, sizeof(rbuf), &rlen, 0) != FALSE)	//接受服务发送过来的内容
			{
				
				printf("接收主进程信息: data = %s, length = %d\n", rbuf, rlen);

				//转换数据到命令结构体
				split(rbuf, ',', vtStrCommand);

				//判断第一元素是否为C2S
				if (vtStrCommand[0].compare(C2S))
				{
					printf("第一元素不能解析，丢弃数据\n");
					continue;
				}
				//命令分析，派发处理。
				if (strcmp(vtStrCommand[1].c_str(), "FF") == 0)
				{
					GET_T->closeCanDev();
					sprintf_s(wbuf, 256, "%s,%d,%s", S2C, enCANDeviErrorCode::Success, "CAN通讯进程即将退出。\n");
					sendToClint();
					Sleep(1000);
					break;
				}
				else if (vtStrCommand[1].compare("F1") == 0)
				{
					static int count = 0;
					printf("openCAN 函数进入%d次\n", ++count);
					//打开设备
					openCAN(wbuf);
					sendToClint();
				}
				else if (GET_T->isOpenCanDev() == false)
				{
					sprintf_s(wbuf, 256, "%s,%d,%s", S2C, enCANDeviErrorCode::DetailError, "CAN设备未打开.\n");
				}
				else if (strcmp(vtStrCommand[1].c_str(), "F2") == 0)
				{
					//关闭设备
					closeCAN(wbuf);
				}
				else if (strcmp(vtStrCommand[1].c_str(), "F3") == 0)
				{
					//读取/设置CAN ID
					readOrWriteCANID(vtStrCommand, wbuf);
				}
				else if (strcmp(vtStrCommand[1].c_str(), "F4") == 0)
				{

				}
				else if (strcmp(vtStrCommand[1].c_str(), "F5") == 0)
				{

				}
				else if (strcmp(vtStrCommand[1].c_str(), "F6") == 0)
				{

				}
				if (strcmp(wbuf, "") != 0)
				{
					//wbuf 不等与"" 代表有
					//printf("wbuf 不为空！\n");
					//sendToClint();
					
				}
			}
		}
	}
	CloseHandle(hPipe);
	return 0;



	int a = 0;
	displayOption();
	while (true)
	{
		scanf_s("%d", &a);
		switch (a)
		{
		case  0:
			return 0;
			break;
		case  1:
			//openCAN();
			break;
		case  2:
			readCanId();
			break;
		case  3:
			writeCanId();
			break; 
		case  4:
				sendVerify();
				break;
		case  5:
			readBeginMode();
			break;
		case  6:
			readMaxCharge();
			break;
		case  7:
			readOrWriteCharge();
			break;
		case  8:
			readLoadAppInfo();
			break;
		case  9:
			readStaticData();
			break;
		case  10:
			readDynaData();
			break;
		case  11:
			readOrWriteDisC();
			break;
		default:
			printf("未知命令，请重新输入\n");
			break;
		}
	}
	
	
	 
}

