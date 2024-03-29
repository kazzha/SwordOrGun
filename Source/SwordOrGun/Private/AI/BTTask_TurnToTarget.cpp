
#include "AI/BTTask_TurnToTarget.h"
#include "Controllers/SAIController.h"
#include "Characters/SNonPlayerCharacter2.h"
#include "Characters/SMonster.h"
#include "Characters/SCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("TurnToTargetActor");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ASAIController* AIC = Cast<ASAIController>(OwnerComp.GetAIOwner());
	if (true == ::IsValid(AIC))
	{
		ASNonPlayerCharacter2* NPC = Cast<ASNonPlayerCharacter2>(AIC->GetPawn());
		if (true == ::IsValid(NPC))
		{
			if (ASCharacter* TargetPC = Cast<ASCharacter>
				(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AIC->TargetActorKey)))
			{
				FVector LookVector = TargetPC->GetActorLocation() - NPC->GetActorLocation();
				LookVector.Z = 0.f;
				FRotator TargetRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
				NPC->SetActorRotation(FMath::RInterpTo(NPC->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 2.f));

				return Result = EBTNodeResult::Succeeded;
			}
		}
		else
		{
			ASMonster* Monster = Cast<ASMonster>(AIC->GetPawn());
			if (ASCharacter* TargetPC = Cast<ASCharacter>
				(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AIC->TargetActorKey)))
			{
				FVector LookVector = TargetPC->GetActorLocation() - Monster->GetActorLocation();
				LookVector.Z = 0.f;
				FRotator TargetRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
				Monster->SetActorRotation(FMath::RInterpTo(Monster->GetActorRotation(), TargetRotation, GetWorld()->GetDeltaSeconds(), 2.f));

				return Result = EBTNodeResult::Succeeded;
			}
		}

	}


	return Result = EBTNodeResult::Failed;
}
