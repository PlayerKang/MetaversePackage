// KDW


#include "LoginGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "BasePlayerController.h"
#include "MetaCharacter.h"
#include "LoginWidget.h"
#include "IPAddress.h"

//TCP
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "IPAddress.h"

ALoginGameMode::ALoginGameMode()
{
	PlayerControllerClass = ABasePlayerController::StaticClass();
	DefaultPawnClass = AMetaCharacter::StaticClass();

	//Widget Create
	static ConstructorHelpers::FClassFinder<ULoginWidget> LoginWidgetClass(TEXT("/Game/LoginWidget"));
	if (LoginWidgetClass.Succeeded())
	{
		ULoginWidget* LoginWidget = CreateWidget<ULoginWidget>(GetWorld(), LoginWidgetClass.Class);

		// UMG_Login 위젯 화면에 추가하기
		if (LoginWidget != nullptr)
		{
			LoginWidget->AddToViewport();

			UE_LOG(LogTemp, Warning, TEXT("Widget ON"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Widget Fail"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Just Do it again"));
	}
}

void ALoginGameMode::StartPlay()
{
	Super::StartPlay();
}

void ALoginGameMode::OnPostLogin(AController* NewPlayer)
{
	Super::OnPostLogin(NewPlayer);
}

void ALoginGameMode::ClientTCPInfo()
{
	ClientSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("DefaultSocket"), false);
	ClientAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

	FString IP = TEXT("127.0.0.1");	//tcp ip
	int32 port = 8080;	//tcp port
	FIPv4Address TemporaryAddr;		//임시 저장소
	FIPv4Address::Parse(IP, TemporaryAddr); //ip를 temporaryAddr에 변환해서 넣고
	ClientAddress->SetPort(port);	//port넣음
	ClientAddress->SetIp(TemporaryAddr.Value);	//ip넣음

	if (ClientSocket->Connect(*ClientAddress))
	{
		UE_LOG(LogTemp, Warning, TEXT("Client : TCP Server IN"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Client : TCP Server In Failed"));
	}

	int MyClientServer = 2;
	uint8_t buffer[sizeof(int)];
	memcpy(buffer, &MyClientServer, sizeof(int));

	int32 bytesSent = 0;
	if (ClientSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
	{
		ClientSocket->Send(buffer, sizeof(int), bytesSent);
	}


	struct ServerData
	{
		uint16_t ServerPort;
		char IP[16];
	};
	ServerData SData;
	uint8_t DBBuffer[1024] = { 0, };
	int32 bytes = 0;
	int ClientServerRecvBytes = 0;

	UE_LOG(LogTemp, Warning, TEXT("TCP DB Data...."));

	if (ClientSocket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromSeconds(5)))
	{
		ClientServerRecvBytes = ClientSocket->Recv(DBBuffer, sizeof(DBBuffer), bytes);

		if (ClientServerRecvBytes < 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Error"));
		}
		else if (ClientSocket == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Data"));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("In Data"));
			memcpy(&SData, DBBuffer, sizeof(ServerData));

			UE_LOG(LogTemp, Warning, TEXT("%d"), SData.ServerPort);
			FString str(SData.IP);
			str += ":";
			str += FString::FromInt(SData.ServerPort);

			UE_LOG(LogTemp, Warning, TEXT("%s"), *str);

			GetWorld()->GetFirstPlayerController()->ClientTravel(str, TRAVEL_Absolute);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No"));
	}

}
