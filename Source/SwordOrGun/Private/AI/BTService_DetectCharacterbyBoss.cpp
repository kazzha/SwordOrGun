
#include "AI/BTService_DetectCharacterbyBoss.h"
#include "Controllers/SAIController.h"
#include "Characters/SMonster.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/SCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UBTService_DetectCharacterbyBoss::UBTService_DetectCharacterbyBoss()
{
	NodeName = TEXT("DetectCharacterbyBoss");
	Interval = 1.f;
}

void UBTService_DetectCharacterbyBoss::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ASAIController* AIC = Cast<ASAIController>(OwnerComp.GetAIOwner());
	if (true == ::IsValid(AIC))
	{
		ASMonster* Monster = Cast<ASMonster>(AIC->GetPawn());
		if (true == ::IsValid(Monster))
		{
			UWorld* World = Monster->GetWorld();
			if (true == ::IsValid(World))
			{
				FVector CenterPosition = Monster->GetActorLocation();
				float DetectRadius = 500.f;
				float DetectHalfHeight = 400.f;
				FVector TraceVec = Monster->GetActorForwardVector() * DetectHalfHeight;
				FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
				TArray<FOverlapResult> OverlapResults;
				FCollisionQueryParams CollisionQueryParams(NAME_None, false, Monster);
				bool bResult = World->OverlapMultiByChannel(
					OverlapResults,
					CenterPosition,
					CapsuleRot,
					ECollisionChannel::ECC_EngineTraceChannel2,
					FCollisionShape::MakeCapsule(DetectRadius, DetectHalfHeight),
					CollisionQueryParams
				);

				if (true == bResult)
				{
					for (auto const& OverlapResult : OverlapResults)
					{
						ASCharacter* PC = Cast<ASCharacter>(OverlapResult.GetActor());
						if (true == ::IsValid(PC))
						{
							if (true == PC->GetController()->IsPlayerController())
							{
								OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASAIController::TargetActorKey, PC);
								/*
								UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("Detected!")));
								DrawDebugCapsule(World, CenterPosition, DetectHalfHeight, DetectRadius, CapsuleRot, FColor::Red, false, 0.5f);
								DrawDebugPoint(World, PC->GetActorLocation(), 10.f, FColor::Red, false, 0.5f);
								DrawDebugLine(World, Monster->GetActorLocation(), PC->GetActorLocation(), FColor::Red, false, 0.5f, 0u, 3.f);
								*/
								return;
							}

							else
							{
								OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASAIController::TargetActorKey, nullptr);
								//DrawDebugCapsule(World, CenterPosition, DetectHalfHeight, DetectRadius, CapsuleRot, FColor::Green, false, 0.5f);
							}
						}
					}

				}

				else
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsObject(ASAIController::TargetActorKey, nullptr);
				}
				/*
				UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("No target detected...")));
				DrawDebugSphere(World, CenterPosition, DetectRadius, 16, FColor::Green, false, 0.5f);
				*/
			}
		}
	}
}