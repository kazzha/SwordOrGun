#include "AI/BTDecorator_IsInBossAttackRange.h"
#include "Controllers/SAIController.h"
#include "Characters/SMonster.h"
#include "Characters/SCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

const float UBTDecorator_IsInBossAttackRange::BossAttackRange(500.f);

UBTDecorator_IsInBossAttackRange::UBTDecorator_IsInBossAttackRange()
{
	NodeName = TEXT("IsInBossAttackRange");
}

bool UBTDecorator_IsInBossAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ASAIController* AIC = Cast<ASAIController>(OwnerComp.GetAIOwner());
	if (true == ::IsValid(AIC))
	{
		ASMonster* Monster = Cast<ASMonster>(AIC->GetPawn());
		if (true == ::IsValid(Monster))
		{
			ASCharacter* TargetPlayerCharacter = Cast<ASCharacter>
				(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASAIController::TargetActorKey));
			if (true == ::IsValid(TargetPlayerCharacter))
			{
				return bResult = (Monster->GetDistanceTo(TargetPlayerCharacter) <= BossAttackRange);
			}

		}
	}
	return bResult = false;
}