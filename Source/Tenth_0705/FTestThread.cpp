#include "FTestThread.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "IPAddress.h"

#include "USingleton.h"



FTestThread::FTestThread()
{
	
}

FTestThread::FTestThread(const FString& m) : Message(m)
{
	
}

FTestThread::~FTestThread()
{
	//스레드 삭제
	if (thread)
	{
		UE_LOG(LogTemp, Warning, TEXT("Thread End"));
		delete thread;
	}
}

bool FTestThread::Init()
{
	bRunThread = true;

	//TCP소켓 생성 연결
	//현재 플렛폼에 맞춰서 소켓을 가져오는 시스템 (새로운 소켓 생성, 소켓 이름, 비차단모드로 설정할지?)
	DediServerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("DefaultSocket"), false);
	DediServerAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	FString IP = TEXT("127.0.0.1");	//tcp ip
	int32 port = 10000;	//tcp port
	FIPv4Address TemporaryAddr;		//임시 저장소
	FIPv4Address::Parse(IP, TemporaryAddr); //ip를 temporaryAddr에 변환해서 넣고
	DediServerAddress->SetPort(port);	//port넣음
	DediServerAddress->SetIp(TemporaryAddr.Value);	//ip넣음

	if (DediServerSocket->Connect(*DediServerAddress))
	{
		UE_LOG(LogTemp, Warning, TEXT("TCP IN Success"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TCP IN Failed"));
	}

	return true;
}

uint32 FTestThread::Run()
{
	UE_LOG(LogTemp, Warning, TEXT("Send Thread"));

	while (bRunThread)
	{
		//소켓과 연결이 끊어지면 종료
		if (DediServerSocket->GetConnectionState() != ESocketConnectionState::SCS_Connected) break;

		////받아온 메세지를 uint8 데이터로 변환
		//FString MessageToSend = FString::FromInt(UUSingleton::GetInstance()->GetData().PlayerNum);	//int > fstring변환
		//MessageToSend += FString::FromInt(UUSingleton::GetInstance()->GetData().ServerPort);
		//MessageToSend += UUSingleton::GetInstance()->GetData().IP;

		//uint8* Data = (uint8*)TCHAR_TO_UTF8(*MessageToSend);
		//int32 BytesSent = 0;

		//if (DediServerSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
		//{
		//	DediServerSocket->Send(Data, MessageToSend.Len(), BytesSent);
		//	//DediServerSocket->Send(Data, sizeof(Data), BytesSent);	//데이터전송
		//	bRunThread = false;
		//}

		bOneDediTCPInfo = UUSingleton::GetInstance()->GetBool();

		if (bOneDediTCPInfo)
		{
			//20230424 받아온 메세지를 Mydata 구조체에 저장하고 구조체를 전송
			MyData data;
			data.MyServer = (int)1;
			data.PlayerNum = UUSingleton::GetInstance()->GetData().PlayerNum;
			data.ServerPort = UUSingleton::GetInstance()->GetData().ServerPort;

			UE_LOG(LogTemp, Warning, TEXT("Thread Port : %d"), UUSingleton::GetInstance()->GetData().ServerPort);
			UE_LOG(LogTemp, Warning, TEXT("Thread IP : %s"), *UUSingleton::GetInstance()->GetData().IP);

			//FString 변수에 저장된 IP 를 char 로 변환하고 strncpy_s 함수를 사용해 char 배열에 복사
			strncpy_s(data.IP, sizeof(data.IP), TCHAR_TO_ANSI(*UUSingleton::GetInstance()->GetData().IP), _TRUNCATE);
			//패킹된 데이터를 보내기 위해 uint8 배열에 복사
			uint8_t buffer[sizeof(MyData)];
			memcpy(buffer, &data, sizeof(MyData));
			//데이터 전송
			int32 bytesSent = 0;
			if (DediServerSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
			{
				DediServerSocket->Send(buffer, sizeof(MyData), bytesSent);
				
				UUSingleton::GetInstance()->SerBool(false);
				bOneDediTCPInfo = false;
			}

			FPlatformProcess::Sleep(0.1f);	//스레드를 잠시 멈춘다
			//정보를 보냈으니 스레드 종료
			//if (!bRunThread)
			//{
			//	this->Stop();
			//	break;
			//}
		}
	}

	return 0;
}

void FTestThread::Stop()
{
	bRunThread = false;
	
	UE_LOG(LogTemp, Warning, TEXT("Thread End"));
}

