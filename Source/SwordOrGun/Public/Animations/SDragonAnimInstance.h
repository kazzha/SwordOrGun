
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SDragonAnimInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckDelegate);
/**
 * 
 */
UCLASS()
class SWORDORGUN_API USDragonAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

    friend class ASMonster;

public:
    USDragonAnimInstance();

    virtual void NativeInitializeAnimation() override;

    virtual void NativeUpdateAnimation(float DeltaSeconds) override;


private:
    void PlaythrowAnimMontage();

    void PlayBeginPlayAnimMontage();

    UFUNCTION()
    void AnimNotify_CheckHit();

    UFUNCTION()
    void OnMonsterDeath();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USDragonAnimInstance")
    float CurrentSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USDragonAnimInstance")
    FVector Velocity;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USDragonAnimInstance")
    bool bIsFalling = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USDragonAnimInstance")
    uint8 bIsCrouching : 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USDragonAnimInstance", Meta = (AllowPrivateAccess))
    TObjectPtr<class UAnimMontage> ThrowAnimMontage;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USDragonAnimInstance", Meta = (AllowPrivateAccess))
    TObjectPtr<class UAnimMontage> BeginPlayAnimMontage;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "USDragonAnimInstance", Meta = (AllowPrivateAccess))
    uint8 bIsDead : 1;


    FOnCheckDelegate OnCheckDelegate;
};
