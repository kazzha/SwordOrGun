#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API ASGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASGameMode();
	
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	

};
