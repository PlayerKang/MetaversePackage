// KDW

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/EditableText.h"
#include "Components/Button.h"
#include "UObject/ConstructorHelpers.h"

#include "LoginWidget.generated.h"


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



    void NativeConstruct();
    /*void HandleHttpRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bSuccess);*/
	
};
