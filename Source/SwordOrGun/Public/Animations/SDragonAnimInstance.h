
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SDragonAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API USDragonAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

    friend class SMonster;

public:
    USDragonAnimInstance();

    virtual void NativeInitializeAnimation() override;

    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
    void PlaythrowAnimMontage();

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

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "USAnimInstance", Meta = (AllowPrivateAccess))
    uint8 bIsDead : 1;

};