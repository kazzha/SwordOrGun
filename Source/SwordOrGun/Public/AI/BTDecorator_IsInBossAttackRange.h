// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsInBossAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API UBTDecorator_IsInBossAttackRange : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IsInBossAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory) const override;

public:
	static const float BossAttackRange;

};
