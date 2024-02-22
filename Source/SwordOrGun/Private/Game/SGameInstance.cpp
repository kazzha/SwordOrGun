#include "Game/SGameInstance.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void USGameInstance::Init()
{
    Super::Init();
    if (false == ::IsValid(CharacterStatDataTable) || CharacterStatDataTable->GetRowMap().Num() <= 0)
    {
        // CharacterStatDataTable->GetRowMap().Num() : 0줄 이하이면
        UE_LOG(LogTemp, Error, TEXT("Not enuough data in CharacterStatDataTable."));
    }
    else
    {
        for (int32 i = 1; i <= CharacterStatDataTable->GetRowMap().Num(); ++i)
        {
            check(nullptr != GetCharacterStatDataTableRow(i));
        }
    }
  
}

void USGameInstance::OnStart()
{
    AudioComponent = UGameplayStatics::SpawnSound2D(GetWorld(), BGM, 1.f, 1.f, 0.f, nullptr, true, true);
}

void USGameInstance::Shutdown()
{
    Super::Shutdown();
}

void USGameInstance::ChangeBGM()
{
    AudioComponent->SetActive(false);
    UGameplayStatics::SpawnSound2D(GetWorld(), BossGroundSound, 1.f, 1.f, 0.f, nullptr, true, true);
}

FSStatTableRow* USGameInstance::GetCharacterStatDataTableRow(int32 InLevel)
{
    if (true == ::IsValid(CharacterStatDataTable))
    {
        return CharacterStatDataTable->FindRow<FSStatTableRow>(*FString::FromInt(InLevel), TEXT(""));
    }
    return nullptr;
}
