
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectCharacterbyBoss.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API UBTService_DetectCharacterbyBoss : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_DetectCharacterbyBoss();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
