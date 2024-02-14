
#include "AI/BTTask_Attack.h"
#include "Controllers/SAIController.h"
#include "Characters/SNonPlayerCharacter2.h"
#include "Characters/STPSNonPlayerCharacter.h"
#include "Characters/SMonster.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	ASAIController* AIC = Cast<ASAIController>(OwnerComp.GetAIOwner());
	if (true == ::IsValid(AIC))
	{
		ASNonPlayerCharacter2* NPC = Cast<ASNonPlayerCharacter2>(AIC->GetPawn());
		ASMonster* Monster = Cast<ASMonster>(AIC->GetPawn());
		if (true == ::IsValid(NPC))
		{
			if (false == NPC->IsNowAttacking())
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}
		else if(true == ::IsValid(Monster))
		{
			if (false == Monster->IsNowAttacking())
			{
				FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
			}
		}

	}
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ASAIController* AIC = Cast<ASAIController>(OwnerComp.GetAIOwner());
	if (true == ::IsValid(AIC))
	{
		ASNonPlayerCharacter2* NPC = Cast<ASNonPlayerCharacter2>(AIC->GetPawn());
		ASMonster* Monster = Cast<ASMonster>(AIC->GetPawn());
		if (true == ::IsValid(NPC))
		{
			NPC->Attack();
		}
		else if(true == ::IsValid(Monster))
		{
			Monster->Attack();
		}
	}

	return EBTNodeResult::InProgress;
}
