
#include "AI/BTService_DetectByPerception.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/SCharacter.h"
#include "Controllers/SAIController.h"

const FName UBTService_DetectByPerception::TargetActorLocationKey(TEXT("TargetLocation"));
const FName UBTService_DetectByPerception::TargetActorLengthKey(TEXT("TargetLength"));

UBTService_DetectByPerception::UBTService_DetectByPerception()
{
	NodeName = TEXT("DetectByPerception");
	Interval = 1.f;
}

void UBTService_DetectByPerception::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ACharacter* PlayerPawn = Cast<ASCharacter>(OwnerComp.GetAIOwner()->GetCharacter());

	UObject* TargetKey = OwnerComp.GetBlackboardComponent()->GetValueAsObject(ASAIController::TargetActorKey);
	if (TargetKey)
	{
		AActor* Target = Cast<AActor>(TargetKey);

		if (true == ::IsValid(Target))
		{
			OwnerComp.GetBlackboardComponent()->SetValueAsVector(TargetActorLocationKey,
				Target->GetActorLocation());

			float length = FMath::Abs<float>(FVector::Dist(
				Target->GetActorLocation(), PlayerPawn->GetActorLocation()
			));

			OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TargetActorLengthKey, length);

		}
	}
}
