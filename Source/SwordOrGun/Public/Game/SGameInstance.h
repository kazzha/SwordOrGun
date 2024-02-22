#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Engine/AssetManager.h"
#include "SGameInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCurrentDeathCountDelegate, int32, deathCount);

USTRUCT(BlueprintType)
struct FSStatTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	FSStatTableRow()
	{
	}

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxEXP;
};

UCLASS()
class SWORDORGUN_API USGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	virtual void Init() override;

	virtual void OnStart() override;

	virtual void Shutdown() override;

	void ChangeBGM();

	const UDataTable* GetCharacterStatDataTable() { return CharacterStatDataTable; }

	FSStatTableRow* USGameInstance::GetCharacterStatDataTableRow(int32 InLevel);

	FStreamableManager StreamableManager = FStreamableManager();

	int32 GetDeathCount() { return CheckDeathCount; }

	FOnCurrentDeathCountDelegate OnCurrentDeathCountDelegate;

	void SetDeathCount(int32 input) { CheckDeathCount = input; OnCurrentDeathCountDelegate.Broadcast(CheckDeathCount); }


public:
	

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "USGameInstance", Meta = (AllowPrivateAccess))
	class UDataTable* CharacterStatDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BGM", Meta = (AllowPrivateAccess))
	TObjectPtr<class USoundBase> BGM;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BGM", Meta = (AllowPrivateAccess))
	TObjectPtr<class USoundBase> BossGroundSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BGM", Meta = (AllowPrivateAccess))
	class UAudioComponent* AudioComponent;

	int32 CheckDeathCount = 0;
};
