
#include "Controllers/SAIController.h"
#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Characters/SCharacter.h"

const float ASAIController::PatrolRadius(500.f);
const FName ASAIController::StartPatrolPositionKey(TEXT("StartPatrolPosition"));
const FName ASAIController::EndPatrolPositionKey(TEXT("EndPatrolPosition"));
const FName ASAIController::TargetActorKey(TEXT("TargetActor"));
const FName ASAIController::CanSeePlayerKey(TEXT("CanSeePlayer"));

const float ASAIController::AI_SIGHT_RADIUS = 2500.f;
const float ASAIController::AI_SIGHT_AGE = 5.f;
const float ASAIController::AI_LOSE_SIGHT_RADIUS = AI_SIGHT_RADIUS + 100.f;
const float ASAIController::AI_FIELD_OF_VIEW = 90.f;

ASAIController::ASAIController()
{
    Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard"));
    BrainComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BrainComponent"));

    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

    if(SightConfig)
    {
        SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception")));

        SightConfig->SightRadius = AI_SIGHT_RADIUS;
        SightConfig->LoseSightRadius = AI_LOSE_SIGHT_RADIUS;
        SightConfig->PeripheralVisionAngleDegrees = AI_FIELD_OF_VIEW;
        SightConfig->SetMaxAge(AI_SIGHT_AGE);

        SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.0f;

        SightConfig->DetectionByAffiliation.bDetectEnemies = true;
        SightConfig->DetectionByAffiliation.bDetectNeutrals = false;
        SightConfig->DetectionByAffiliation.bDetectFriendlies = false;

        GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
        GetPerceptionComponent()->ConfigureSense(*SightConfig);

        GetAIPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ASAIController::TargetPerceptionUpdated);
    }
    
}


void ASAIController::BeginAI(APawn* InPawn)
{
    UBlackboardComponent* BlackboardComponent = Cast<UBlackboardComponent>(Blackboard);
    if (true == ::IsValid(BlackboardComponent))
    {
        if (true == UseBlackboard(BlackboardDataAsset, BlackboardComponent))
        {
            bool bRunSucceeded = RunBehaviorTree(BehaviorTree);
            ensure(true == bRunSucceeded);
            BlackboardComponent->SetValueAsVector(StartPatrolPositionKey, InPawn->GetActorLocation());
        }
    }
}
  
void ASAIController::EndAI()
{
    UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
    if (true == ::IsValid(BehaviorTreeComponent))
    {
        BehaviorTreeComponent->StopTree();
        UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("EndAI() has been called.")));
    }
}

void ASAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* ControlledPawn = GetPawn();
    if (true == ::IsValid(ControlledPawn))
    {
        BeginAI(ControlledPawn);
    }
}


void ASAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    EndAI();
}

void ASAIController::OnPatrolTimerElapsed()
{
    APawn* ControlledPawn = GetPawn();
    if (true == ::IsValid(ControlledPawn))
    {
        UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());
        if (true == ::IsValid(NavSystem))
        {
            FNavLocation NextLocation;
            if (true == NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, PatrolRadius, NextLocation))
            {
                UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
            }
        }
    }
}

void ASAIController::TargetPerceptionUpdated(AActor* UpdatedActor, FAIStimulus Stimulus)
{
    if (auto player = Cast<ASCharacter>(UpdatedActor))
    {
        UBlackboardComponent* BlackboardComponent = Cast<UBlackboardComponent>(Blackboard);
        BlackboardComponent->SetValueAsBool(CanSeePlayerKey, Stimulus.WasSuccessfullySensed());
        BlackboardComponent->SetValueAsObject(ASAIController::TargetActorKey, player);
    }
}
