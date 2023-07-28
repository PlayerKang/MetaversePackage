//KDW


#include "LoginWidget.h"
#include "Kismet/GameplayStatics.h"
#include "LoginGameMode.h"

//TCP
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"
#include "IPAddress.h"

void ULoginWidget::OnLoginButtonClicked()
{
    if (Id && Id->HasKeyboardFocus())
    {
        FID = Id->GetText().ToString();
    }
    else if (Password && Password->HasKeyboardFocus())
    {
        FPassword = Password->GetText().ToString();
    }

    //TCP로 전송, 로그인
    MyLoginData LoginData;
    strncpy(LoginData.Email, TCHAR_TO_ANSI(*FID), sizeof(LoginData.Email) - 1);
    strncpy(LoginData.Password, TCHAR_TO_ANSI(*FPassword), sizeof(LoginData.Password) - 1);
    LoginData.type = 1;

    uint8_t buffer[sizeof(MyLoginData)];
    memcpy(buffer, &LoginData, sizeof(MyLoginData));
    //데이터 전송
    int32 bytesSent = 0;
    if (LoginServerSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
    {
        LoginServerSocket->Send(buffer, sizeof(MyLoginData), bytesSent);
        UE_LOG(LogTemp, Warning, TEXT("Send Login Data"));
    }
}

void ULoginWidget::OnCreateSignUpButtonClicked()
{
    
}

void ULoginWidget::OnSignUpButtonClicked()
{
    if (Id && Id->HasKeyboardFocus())
    {
        FID = Id->GetText().ToString();

    }
    else if (Password && Password->HasKeyboardFocus())
    {
        FPassword = Password->GetText().ToString();
    }

    //TCP로 전송, 사인업

    MyLoginData LoginData;
    strncpy(LoginData.Email, TCHAR_TO_ANSI(*FID), sizeof(LoginData.Email) - 1);
    strncpy(LoginData.Password, TCHAR_TO_ANSI(*FPassword), sizeof(LoginData.Password) - 1);
    LoginData.type = 0;

    uint8_t buffer[sizeof(MyLoginData)];
    memcpy(buffer, &LoginData, sizeof(MyLoginData));
    //데이터 전송
    int32 bytesSent = 0;
    if (LoginServerSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
    {
        LoginServerSocket->Send(buffer, sizeof(MyLoginData), bytesSent);
        UE_LOG(LogTemp, Warning, TEXT("Send SignUp Data"));
    }
}

void ULoginWidget::OnBackButtonClicked()
{
}

void ULoginWidget::NativeConstruct()
{
    UButton* LoginButton = Cast<UButton>(GetWidgetFromName(TEXT("Login")));
    UButton* SignUpButton = Cast<UButton>(GetWidgetFromName(TEXT("signup")));
    // 버튼 이벤트 핸들러 등록하기
    if (LoginButton)
    {
        LoginButton->OnClicked.AddDynamic(this, &ULoginWidget::OnLoginButtonClicked);
    }
    if (SignUpButton)
    {
        SignUpButton->OnClicked.AddDynamic(this, &ULoginWidget::OnCreateSignUpButtonClicked);

    }

    UButton* CreateSignUpButton = Cast<UButton>(GetWidgetFromName(TEXT("createsignup")));

    UButton* BackButton = Cast<UButton>(GetWidgetFromName(TEXT("back")));
    // 버튼 이벤트 핸들러 등록하기
    if (CreateSignUpButton)
    {
        CreateSignUpButton->OnClicked.AddDynamic(this, &ULoginWidget::OnSignUpButtonClicked);
    }
    if (BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &ULoginWidget::OnBackButtonClicked);
    }


    //TCP 연결 위젯에 때려박기

    LoginServerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("DefaultSocket"), false);
    LoginServerAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

    FString IP = TEXT("127.0.0.1");	//tcp ip
    int32 port = 8080;	//tcp port
    FIPv4Address TemporaryAddr;		//임시 저장소
    FIPv4Address::Parse(IP, TemporaryAddr); //ip를 temporaryAddr에 변환해서 넣고
    LoginServerAddress->SetPort(port);	//port넣음
    LoginServerAddress->SetIp(TemporaryAddr.Value);	//ip넣음

    if (LoginServerSocket->Connect(*LoginServerAddress))
    {
        UE_LOG(LogTemp, Warning, TEXT("Widget TCP IN Success"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Widget TCP IN Failed"));
    }

}
