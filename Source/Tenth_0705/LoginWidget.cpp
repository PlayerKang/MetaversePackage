//KDW


#include "LoginWidget.h"
#include "Kismet/GameplayStatics.h"
#include "LoginGameMode.h"

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
        UE_LOG(LogTemp, Warning, TEXT("Login Button Event"));
    }
    if (SignUpButton)
    {
        SignUpButton->OnClicked.AddDynamic(this, &ULoginWidget::OnCreateSignUpButtonClicked);
        UE_LOG(LogTemp, Warning, TEXT("Move To SignUp Event"));

    }

    UButton* CreateSignUpButton = Cast<UButton>(GetWidgetFromName(TEXT("CreateSignUpButton")));

    UButton* BackButton = Cast<UButton>(GetWidgetFromName(TEXT("BackButton")));
    // 버튼 이벤트 핸들러 등록하기
    if (CreateSignUpButton)
    {
        CreateSignUpButton->OnClicked.AddDynamic(this, &ULoginWidget::OnSignUpButtonClicked);
    }
    if (BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &ULoginWidget::OnBackButtonClicked);
    }
}
