
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "SAIController.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API ASAIController : public AAIController
{
	GENERATED_BODY()
	
public:
    ASAIController();

    void BeginAI(APawn* InPawn);

    void EndAI();

protected:
    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    void OnPatrolTimerElapsed();

    UFUNCTION()
    void TargetPerceptionUpdated(AActor* UpdatedActor, FAIStimulus Stimulus);

    ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;



public:
    /*
    FTimerHandle PatrolTimerHandle = FTimerHandle();

    static const float PatrolRepeatInterval;
    */
    static const float PatrolRadius;

    static const FName StartPatrolPositionKey;

    static const FName EndPatrolPositionKey;

    static const FName TargetActorKey;

    static const FName CanSeePlayerKey;

    static const float AI_SIGHT_RADIUS;
    static const float AI_SIGHT_AGE;
    static const float AI_LOSE_SIGHT_RADIUS;
    static const float AI_FIELD_OF_VIEW;

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ASAIController, meta = (AllowPrivateAccess))
    TObjectPtr<class UBlackboardData> BlackboardDataAsset;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ASAIController, meta = (AllowPrivateAccess))
    TObjectPtr<class UBehaviorTree> BehaviorTree;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASAIController, meta = (AllowPrivateAccess))
    TObjectPtr<class UAISenseConfig_Sight> SightConfig;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ASAIController, meta = (AllowPrivateAccess = "true"))
    float AISightRadius = 500.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ASAIController, meta = (AllowPrivateAccess = "true"))
    float AISightAge = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ASAIController, meta = (AllowPrivateAccess = "true"))
    float AILoseSightRadius = AISightRadius + 50.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ASAIController, meta = (AllowPrivateAccess = "true"))
    float AIFieldOfView = 90.0f;
};
