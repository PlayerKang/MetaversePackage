// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "USingleton.generated.h"


UCLASS()
class TENTH_0705_API UUSingleton : public UObject
{
	GENERATED_BODY()


public:
	static UUSingleton* GetInstance();

	struct Data
	{
		int PlayerNum;
		int ServerPort;
		FString IP;
	};
	
	const Data& GetData() { return data; }
	void SetData(int playernum, int serverport, FString ip);

	bool GetBool() const { return singletonbool; }
	void SerBool(bool val) { singletonbool = val; }

private:
	UUSingleton()
	{
		data.PlayerNum = 0;
	}
	static UUSingleton* instance;
	static TSubclassOf<UUSingleton> SingletonClass;

	Data data;
	bool singletonbool;
};

UUSingleton* UUSingleton::instance = NULL;	//싱글톤 초기화
