// KDW

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/EditableText.h"
#include "Components/Button.h"
#include "UObject/ConstructorHelpers.h"

#include "LoginWidget.generated.h"


#pragma pack(push, 1)
struct MyLoginData
{
    char Email[30];
    char Password[30];
};
#pragma pack(pop)


UCLASS()
class TENTH_0705_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite)
        UEditableText* Id;

    UPROPERTY(BlueprintReadWrite)
        UEditableText* Password;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FString FID;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
        FString FPassword;

    UFUNCTION(BlueprintCallable)
        void OnLoginButtonClicked();

    UFUNCTION(BlueprintCallable)
        void OnCreateSignUpButtonClicked();

    UFUNCTION(BlueprintCallable)
        void OnSignUpButtonClicked();

    UFUNCTION(BlueprintCallable)
        void OnBackButtonClicked();

private:
    FString Message;
    TSharedPtr<FInternetAddr> DediServerAddress;
    class FSocket* DediServerSocket;


    void NativeConstruct();
    /*void HandleHttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);*/
	
};
