// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TENTH_0705_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABasePlayerController() { };
	virtual void BeginPlay() override;
	
};
