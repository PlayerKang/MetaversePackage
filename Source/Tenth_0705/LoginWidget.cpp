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

    //TCP�� ����, �α���
    MyLoginData LoginData;
    strncpy(LoginData.Email, TCHAR_TO_ANSI(*FID), sizeof(LoginData.Email) - 1);
    strncpy(LoginData.Password, TCHAR_TO_ANSI(*FPassword), sizeof(LoginData.Password) - 1);
    LoginData.type = 1;

    uint8_t buffer[sizeof(MyLoginData)];
    memcpy(buffer, &LoginData, sizeof(MyLoginData));
    //������ ����
    int32 bytesSent = 0;
    if (DediServerSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
    {
        DediServerSocket->Send(buffer, sizeof(MyLoginData), bytesSent);
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

    //TCP�� ����, ���ξ�

    MyLoginData LoginData;
    strncpy(LoginData.Email, TCHAR_TO_ANSI(*FID), sizeof(LoginData.Email) - 1);
    strncpy(LoginData.Password, TCHAR_TO_ANSI(*FPassword), sizeof(LoginData.Password) - 1);
    LoginData.type = 0;

    uint8_t buffer[sizeof(MyLoginData)];
    memcpy(buffer, &LoginData, sizeof(MyLoginData));
    //������ ����
    int32 bytesSent = 0;
    if (DediServerSocket->GetConnectionState() == ESocketConnectionState::SCS_Connected)
    {
        DediServerSocket->Send(buffer, sizeof(MyLoginData), bytesSent);
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
    // ��ư �̺�Ʈ �ڵ鷯 ����ϱ�
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
    // ��ư �̺�Ʈ �ڵ鷯 ����ϱ�
    if (CreateSignUpButton)
    {
        CreateSignUpButton->OnClicked.AddDynamic(this, &ULoginWidget::OnSignUpButtonClicked);
    }
    if (BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &ULoginWidget::OnBackButtonClicked);
    }


    //TCP ���� ������ �����ڱ�

    DediServerSocket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("DefaultSocket"), false);
    DediServerAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();

    FString IP = TEXT("127.0.0.1");	//tcp ip
    int32 port = 8080;	//tcp port
    FIPv4Address TemporaryAddr;		//�ӽ� �����
    FIPv4Address::Parse(IP, TemporaryAddr); //ip�� temporaryAddr�� ��ȯ�ؼ� �ְ�
    DediServerAddress->SetPort(port);	//port����
    DediServerAddress->SetIp(TemporaryAddr.Value);	//ip����

    if (DediServerSocket->Connect(*DediServerAddress))
    {
        UE_LOG(LogTemp, Warning, TEXT("TCP IN Success"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("TCP IN Failed"));
    }

}
