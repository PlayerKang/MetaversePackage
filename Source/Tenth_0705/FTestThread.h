#pragma once

#include "CoreMinimal.h"

#pragma pack(push, 1)
struct MyData
{
	int MyServer;
	int PlayerNum;
	uint16_t ServerPort;
	char IP[16];
};
#pragma pack(pop)

class TENTH_0705_API FTestThread : public FRunnable
{
public:
	FTestThread();
	FTestThread(const FString& m);
	~FTestThread() override;

	bool Init() override;
	virtual uint32 Run() override;	//데이터를 보내는
	virtual void Stop() override;	//스레드 중지
	bool IsThreadRunning() const;

	class FSocket* ServerSocket = nullptr;

	FString RecvText = "";

private:
	FString Message;
	TSharedPtr<FInternetAddr> DediServerAddress = nullptr;
	class FSocket* DediServerSocket;
	class FRunnableThread* thread = nullptr;

	bool bRunThread = false;
	bool bOneDediTCPInfo = false;

	bool bIsThreadRunning = false;
};
 