#include "USingleton.h"

UUSingleton* UUSingleton::GetInstance()
{
    if (instance == NULL)
    {
        instance = NewObject<UUSingleton>();
    }
    return instance;
}

void UUSingleton::SetData(int playernum, int serverport, FString ip)
{
    data.PlayerNum = playernum;
    data.ServerPort = serverport;
    data.IP = ip;

    UE_LOG(LogTemp, Error, TEXT("Singleton Port : %d"), data.ServerPort);
    UE_LOG(LogTemp, Error, TEXT("Singleton IP : %s"), *data.IP);
}












