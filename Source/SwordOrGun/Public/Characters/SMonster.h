#pragma once

#include "CoreMinimal.h"
#include "Characters/SCharacter.h"
#include "SMonster.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API ASMonster : public ASCharacter
{
	GENERATED_BODY()

	friend class UBTTask_Attack;
	
public:
	ASMonster();

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
	float AttackRange = 400.f;

	float AttackRadius = 150.f;

	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SMonster", Meta = (AllowPrivateAccess))
	TObjectPtr<class USWidgetComponent> WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SMonster", Meta = (AllowPrivateAccess))
	TObjectPtr<class UAIPerceptionStimuliSourceComponent> AIStimuliSource;

	
};
