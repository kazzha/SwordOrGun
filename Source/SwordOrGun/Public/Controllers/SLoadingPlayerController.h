#pragma once

#include "CoreMinimal.h"
#include "Controllers/SUIPlayerController.h"
#include "SLoadingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API ASLoadingPlayerController : public ASUIPlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
};
