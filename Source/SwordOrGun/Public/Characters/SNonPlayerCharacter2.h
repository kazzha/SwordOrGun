#pragma once

#include "CoreMinimal.h"
#include "Characters/SCharacter.h"
#include "SNonPlayerCharacter2.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API ASNonPlayerCharacter2 : public ASCharacter
{
	GENERATED_BODY()

	friend class UBTTask_Attack;

public:
	ASNonPlayerCharacter2();

	virtual void BeginPlay() override;

	bool IsNowAttacking() const { return bIsAttacking; }

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	virtual void SetWidget(class USwordUserWidget* InSwordUserWidget) override;



private:
	void Attack();
	
	void DropItems();

	void SpawnDragon(APlayerController* PlayerController);

	UFUNCTION()
	void OnAttackAnimMontageEnded(class UAnimMontage* Montage, bool bIsInterrupt);

private:
	float AttackRange = 200.f;

	float AttackRadius = 50.f;

	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASNonPlayerCharacter2", Meta = (AllowPrivateAccess))
	TObjectPtr<class USWidgetComponent> WidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<class ASItem> ItemToDrop;

	UPROPERTY(EditDefaultsOnly, Category = "Spawn")
	TSubclassOf<class ASMonster> BossMonster;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effect Sound", Meta = (AllowPrivateAccess))
	TObjectPtr<class USoundBase> HitSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Camera Shake", Meta = (AllowPrivateAccess))
	TSubclassOf<class UCameraShakeBase> GroundShake;
};
