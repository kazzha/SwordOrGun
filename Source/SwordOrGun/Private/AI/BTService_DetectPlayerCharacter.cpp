
#include "AI/BTService_DetectPlayerCharacter.h"
#include "Controllers/SAIController.h"
#include "Characters/SNonPlayerCharacter2.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/SCharacter.h"
#include "Characters/SRPGCharacter.h"

UBTService_DetectPlayerCharacter::UBTService_DetectPlayerCharacter()
{
    NodeName = TEXT("DetectPlayerCharacter");
    Interval = 1.f;
}

void UBTService_DetectPlayerCharacter::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ASAIController* AIC = Cast<ASAIController>(OwnerComp.GetAIOwner());
	if (true == ::IsValid(AIC))
	{
		ASNonPlayerCharacter2* NPC = Cast<ASNonPlayerCharacter2>(AIC->GetPawn());
		if (true == ::IsValid(NPC))
		{
			UWorld* World = NPC->GetWorld();
			if (true == ::IsValid(World))
			{
				FVector CenterPosition = NPC->GetActorLocation();
				float DetectRadius = 300.f;
				TArray<FOverlapResult> OverlapResults;
				FCollisionQueryParams CollisionQueryParams(NAME_None, false, NPC);
				bool bResult = World->OverlapMultiByChannel(
					OverlapResults,
					CenterPosition,
					FQuat::Identity,
					ECollisionChannel::ECC_EngineTraceChannel2,
					FCollisionShape::MakeSphere(DetectRadius),
					CollisionQueryParams
				);

				if (true == bResult)
				{
					for (auto const& OverlapResult : OverlapResults)
					{
						ASRPGCharacter* PC = Cast<ASRPGCharacter>(OverlapResult.GetActor());
						if (true == ::IsValid(PC))
						{
							if (true == PC->GetController()->IsPlayerController())
							{
								OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASAIController::TargetActorKey, PC);
								// UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Detected!")));
								/*
								DrawDebugSphere(World, CenterPosition, DetectRadius, 16, FColor::Red, false, 0.5f);
								DrawDebugPoint(World, PC->GetActorLocation(), 10.f, FColor::Red, false, 0.5f);
								DrawDebugLine(World, NPC->GetActorLocation(), PC->GetActorLocation(), FColor::Red, false, 0.5f, 0u, 3.f);
								*/
								return;
							}

							else
							{
								OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASAIController::TargetActorKey, nullptr);
								// DrawDebugSphere(World, CenterPosition, DetectRadius, 16, FColor::Green, false, 0.5f);
							}
						}
					}

				}

				else
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASAIController::TargetActorKey, nullptr);
				}

				// UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("No target detected...")));
				// DrawDebugSphere(World, CenterPosition, DetectRadius, 16, FColor::Green, false, 0.5f);
			}
		}
	}
}