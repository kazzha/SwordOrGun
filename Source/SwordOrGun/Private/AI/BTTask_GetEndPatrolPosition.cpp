#include "AI/BTTask_GetEndPatrolPosition.h"
#include "Controllers/SAIController.h"
#include "Characters/SNonPlayerCharacter2.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/STPSNonPlayerCharacter.h"
#include "Characters/SMonster.h"

UBTTask_GetEndPatrolPosition::UBTTask_GetEndPatrolPosition()
{
    NodeName = TEXT("GetEndPatrolPosition"); 
}

EBTNodeResult::Type UBTTask_GetEndPatrolPosition::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    if (EBTNodeResult::Failed == Result)
    {
        return Result;
    }

    ASAIController* AIController = Cast<ASAIController>(OwnerComp.GetAIOwner());
    if (false == ::IsValid(AIController))
    {
        return Result = EBTNodeResult::Failed;
    }

    ASNonPlayerCharacter2* NPC = Cast<ASNonPlayerCharacter2>(AIController->GetPawn());
    if (false == ::IsValid(NPC))
    {
        ASTPSNonPlayerCharacter* TPSNPC = Cast<ASTPSNonPlayerCharacter>(AIController->GetPawn());
        if (false == ::IsValid(TPSNPC))
        {
            ASMonster* Monster = Cast<ASMonster>(AIController->GetPawn());
            if (false == ::IsValid(Monster))
            {
                return Result = EBTNodeResult::Failed;
            }
        }
    }

    FVector StartPatrolPosition = OwnerComp.GetBlackboardComponent()->GetValueAsVector(ASAIController::StartPatrolPositionKey);

    float RandomX = FMath::RandRange(0, 1) == 0 ? -200.f : 200.f;
    float RandomY = FMath::RandRange(0, 1) == 0 ? -200.f : 200.f;

    FVector EndPatrolLocation = StartPatrolPosition + FVector(RandomX, RandomY, 0.f);

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(ASAIController::EndPatrolPositionKey, EndPatrolLocation);

    return Result;
}