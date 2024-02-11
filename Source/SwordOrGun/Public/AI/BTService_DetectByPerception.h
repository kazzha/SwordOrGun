#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_DetectByPerception.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API UBTService_DetectByPerception : public UBTService
{
	GENERATED_BODY()
public:
	UBTService_DetectByPerception();

	static const FName TargetActorLocationKey;
	static const FName TargetActorLengthKey;

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
