
#include "Animations/SDragonAnimInstance.h"
#include "Characters/SMonster.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SStatComponent.h"

USDragonAnimInstance::USDragonAnimInstance()
{
}

void USDragonAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();

    CurrentSpeed = 0.f;

    Velocity = FVector::ZeroVector;

    bIsFalling = false;

    bIsCrouching = false;

    bIsDead = false;

    ASCharacter* OwnerCharacter = Cast<ASCharacter>(TryGetPawnOwner());

    if (true == ::IsValid(OwnerCharacter))
    {
        USStatComponent* StatComponent = OwnerCharacter->GetStatComponent();
        if (true == ::IsValid(StatComponent))
        {
            if (false == StatComponent->OnOutOfCurrentHPDelegate.IsAlreadyBound(this, &ThisClass::OnMonsterDeath))
            {
                StatComponent->OnOutOfCurrentHPDelegate.AddDynamic(this, &ThisClass::OnMonsterDeath);
            }
        }
    }
}

void USDragonAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);

    ASCharacter* OwnerCharacter = Cast<ASCharacter>(TryGetPawnOwner());
    if (true == ::IsValid(OwnerCharacter))
    {
        UCharacterMovementComponent* CharacterMovementComponent = OwnerCharacter->GetCharacterMovement();
        if (true == ::IsValid(CharacterMovementComponent))
        {
            Velocity = CharacterMovementComponent->GetLastUpdateVelocity();
            CurrentSpeed = Velocity.Size();
            bIsFalling = CharacterMovementComponent->IsFalling();
            bIsCrouching = CharacterMovementComponent->IsCrouching();
            // bIsDead = OwnerCharacter->IsDead();
        }
    }
}

void USDragonAnimInstance::PlaythrowAnimMontage()
{
    if (true == ::IsValid(ThrowAnimMontage))
    {
        if (false == Montage_IsPlaying(ThrowAnimMontage))
        {
            Montage_Play(ThrowAnimMontage);
        }
    }
}

void USDragonAnimInstance::PlayFireAnimMontage()
{
    if (true == ::IsValid(FireAnimMontage))
    {
        if (false == Montage_IsPlaying(FireAnimMontage))
        {
            Montage_Play(FireAnimMontage);
        }
    }
}

void USDragonAnimInstance::PlayBeginPlayAnimMontage()
{
    if (true == ::IsValid(BeginPlayAnimMontage))
    {
        if (false == Montage_IsPlaying(BeginPlayAnimMontage))
        {
            Montage_Play(BeginPlayAnimMontage);
        }
    }
}

void USDragonAnimInstance::AnimNotify_CheckHit()
{
    if (true == OnCheckDelegate.IsBound())
    {
        OnCheckDelegate.Broadcast();
    }
}

void USDragonAnimInstance::OnMonsterDeath()
{
    bIsDead = true;
}
