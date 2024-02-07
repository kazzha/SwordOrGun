#pragma once

#include "CoreMinimal.h"
#include "Characters/SCharacter.h"
#include "InputActionValue.h"
#include "STPSCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API ASTPSCharacter : public ASCharacter
{
	GENERATED_BODY()
	
public:
	ASTPSCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void BeginPlay() override;

	float GetForwardInputValue() const { return ForwardInputValue; }

	float GetRightInputValue() const { return RightInputValue; }

	float GetCurrentAimPitch() const { return CurrentAimPitch; }

	float GetCurrentAimYaw() const { return CurrentAimYaw; }

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent,
		AController* EventInstigator, AActor* DamageCauser) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	void Move(const FInputActionValue& InValue);

	void Look(const FInputActionValue& InValue);

	void Attack(const FInputActionValue& InValue);

	void Fire();

	void StartIronSight(const FInputActionValue& InValue);

	void EndIronSight(const FInputActionValue& InValue);

	void ToggleTrigger(const FInputActionValue& InValue);

	void StartFire(const FInputActionValue& InValue);

	void StopFire(const FInputActionValue& InValue);

	void SpawnLandMine(const FInputActionValue& InValue);

	UFUNCTION()
	void OnHittedRagdollRestoreTimerElapsed();

	UFUNCTION(Server, Reliable, WithValidation)
	void SpawnLandMine_Server();

	UFUNCTION(Server, Unreliable)
	void UpdateInputValue_Server(const float& InForwardInputValue, const float& InRightInputValue);

	UFUNCTION(Server, Unreliable)
	void UpdateAimValue_Server(const float& InAimPitchValue, const float& InAimYawValue);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess))
	TObjectPtr<USkeletalMeshComponent> WeaponSkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess))
	TObjectPtr<class USInputConfigData> PlayerCharacterInputConfigData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess))
	TObjectPtr<class UInputMappingContext> PlayerCharacterInputMappingContext;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess))
	float ForwardInputValue;

	float PreviousForwardInputValue = 0.f;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess))
	float RightInputValue;

	float PreviousRightInputValue = 0.f;

	float TargetFOV = 70.f;
	float CurrentFOV = 70.f;

	bool bIsTriggerToggle = false;

	UPROPERTY(EditDefaultsOnly, Category = "ASTPSCharacter", Meta = (AllowPrivateAccess))
	float FirePerMinute = 600;

	FTimerHandle BetweenShotsTimer;

	float TimerBetweenFire; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ASPlayerCharacter, Meta = (AllowPrivateAccess = true))
	TObjectPtr<class UAnimMontage> RifleFireAnimMontage;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess = true))
	float CurrentAimPitch = 0.f;

	float PreviousAimPitch = 0.f;

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "ASTPSCharacter", meta = (AllowPrivateAccess = true))
	float CurrentAimYaw = 0.f;

	float PreviousAimYaw = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = ASPlayerCharacter, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class UCameraShakeBase> FireShake;

	FTimerHandle HittedRagdollRestoreTimer;

	FTimerDelegate HittedRagdollRestoreTimerDelegate;

	float TargetRagDollBlendWeight = 0.f;

	float CurrentRagDollBlendWeight = 0.f;

	bool bIsNowRagdollBlending = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ASPlayerCharacter, Meta = (AllowPrivateAccess = true))
	TSubclassOf<class AActor> LandMineClass;
};
