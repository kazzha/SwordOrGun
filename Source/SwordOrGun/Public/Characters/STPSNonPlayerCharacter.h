
#pragma once

#include "CoreMinimal.h"
#include "Characters/SCharacter.h"
#include "STPSNonPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API ASTPSNonPlayerCharacter : public ASCharacter
{
	GENERATED_BODY()

	ASTPSNonPlayerCharacter();
	
	virtual void BeginPlay() override;

	bool IsNowAttacking() const { return bIsAttacking; }

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SetWidget(class USwordUserWidget* InSwordUserWidget) override;

private:
	void Attack();

	UFUNCTION()
	void OnAttackAnimMontageEnded(class UAnimMontage* Montage, bool bIsInterrupt);

private:
	
	float AttackRange = 1000.f;

	float AttackRadius = 5.f;

	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASNonPlayerCharacter2", Meta = (AllowPrivateAccess))
	TObjectPtr<class USWidgetComponent> WidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ASPlayerCharacter, Meta = (AllowPrivateAccess = true))
	TObjectPtr<class UAnimMontage> RifleFireAnimMontage;
};
