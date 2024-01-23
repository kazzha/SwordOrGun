
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SAnimInstance.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckHitDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckCanNextComboDelegate);
/**
 * 
 */
UCLASS()
class SWORDORGUN_API USAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

    friend class ASRPGCharacter;
    friend class ASNonPlayerCharacter2;

public:
    USAnimInstance();

    virtual void NativeInitializeAnimation() override;

    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
    void PlayAttackAnimMontage();

    UFUNCTION()
    void AnimNotify_CheckHit();

    UFUNCTION()
    void AnimNotify_CheckCanNextCombo();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USAnimInstance")
    float CurrentSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USAnimInstance")
    FVector Velocity;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USAnimInstance")
    bool bIsFalling = true;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USAnimInstance")
    uint8 bIsCrouching : 1;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USAnimInstance", Meta = (AllowPrivateAccess))
    TObjectPtr<class UAnimMontage> AttackAnimMontage;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "USAnimInstance", Meta = (AllowPrivateAccess))
    uint8 bIsDead : 1;

    FOnCheckHitDelegate OnCheckHitDelegate;

    FOnCheckCanNextComboDelegate OnCheckCanNextComboDelegate;
};
