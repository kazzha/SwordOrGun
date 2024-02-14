
#include "Characters/SNonPlayerCharacter2.h"
#include "Controllers/SAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Animations/SAnimInstance.h"
#include "Characters/SRPGCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SStatComponent.h"
#include "Components/SWidgetComponent.h"
#include "UI/SwordUserWidget.h"
#include "UI/SW_HPBar.h"
#include "Game/SPlayerState.h"
#include "Engine/EngineTypes.h"
#include "Engine/DamageEvents.h"
#include "WorldStatics/SItem.h"
#include "Game/SGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Characters/SMonster.h"

ASNonPlayerCharacter2::ASNonPlayerCharacter2()
{
    PrimaryActorTick.bCanEverTick = false;

    AIControllerClass = ASAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    WidgetComponent = CreateDefaultSubobject<USWidgetComponent>(TEXT("WidgetComponent"));
    WidgetComponent->SetupAttachment(GetRootComponent());
    WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
    WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    WidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f));
    WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    ItemToDrop = ASItem::StaticClass();

}

void ASNonPlayerCharacter2::BeginPlay()
{
    Super::BeginPlay();

    if (false == IsPlayerControlled())
    {
        bUseControllerRotationYaw = false;

        GetCharacterMovement()->bOrientRotationToMovement = false;
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.f, 480.f, 0.f);

        GetCharacterMovement()->MaxWalkSpeed = 300.f;
    }

    USAnimInstance* AnimInstance = Cast<USAnimInstance>(GetMesh()->GetAnimInstance());
    if (true == ::IsValid(AnimInstance) && false == 
        AnimInstance->OnMontageEnded.IsAlreadyBound(this, &ThisClass::OnAttackAnimMontageEnded))
    {
        AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnAttackAnimMontageEnded);
    }
}

float ASNonPlayerCharacter2::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float FinalDamageAmount = Super::TakeDamage(Damage, DamageEvent, EventInstigator,DamageCauser);

    /*
    if (CurrentHP < KINDA_SMALL_NUMBER)
    {
        ASRPGCharacter* DamageCauserCharacter = Cast<ASRPGCharacter>(DamageCauser);
        if (true == ::IsValid(DamageCauserCharacter))
        {
            DamageCauserCharacter->SetCurrentEXP(DamageCauserCharacter->GetCurrentEXP() + 5);
        }

        CurrentHP = 0.f;

        bIsDead = true;
        GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
        ASAIController* AIController = Cast<ASAIController>(GetController());
        if (true == ::IsValid(AIController))
        {
            AIController->EndAI();
        }
    }

    CurrentHP = FMath::Clamp(CurrentHP - FinalDamageAmount, 0.f, MaxHP);

    */

    if (StatComponent->GetCurrentHP() < KINDA_SMALL_NUMBER)
    {
        /*
        ASRPGCharacter* DamageCauserCharacter = Cast<ASRPGCharacter>(DamageCauser);
        if (true == ::IsValid(DamageCauserCharacter))
        {
            DamageCauserCharacter->SetCurrentEXP(DamageCauserCharacter->GetCurrentEXP() + 5);
        }
        */

        if (true == ::IsValid(LastHitBy))
        {
            ASCharacter* DamageCauserCharacter = Cast<ASCharacter>(LastHitBy->GetPawn());
            if (true == ::IsValid(DamageCauserCharacter))
            {
                ASPlayerState* PS = Cast<ASPlayerState>(DamageCauserCharacter->GetPlayerState());
                if (true == ::IsValid(PS))
                {
                    PS->SetCurrentEXP(PS->GetCurrentEXP() + 20.f);
                    DropItems();
                    USGameInstance* GameInstance = Cast<USGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
                    GameInstance->SetDeathCount(GameInstance->GetDeathCount()+1);

                    if (GameInstance->GetDeathCount() == 7)
                    {
                        SpawnDragon();
                    }

                }
            }
        }

        ASAIController* AIController = Cast<ASAIController>(GetController());
        if (true == ::IsValid(AIController))
        {
            AIController->EndAI();
        }
    }

    return FinalDamageAmount;
}

void ASNonPlayerCharacter2::SetWidget(USwordUserWidget* InSwordUserWidget)
{
    USW_HPBar* HPBarWidget = Cast<USW_HPBar>(InSwordUserWidget);
    if (true == ::IsValid(HPBarWidget))
    {
        HPBarWidget->SetMaxHP(StatComponent->GetMaxHP());
        HPBarWidget->InitializeHPBarWidget(StatComponent);
        StatComponent->OnCurrentHPChangeDelegate.AddDynamic(HPBarWidget, &USW_HPBar::OnCurrentHPChange);
    }
}

void ASNonPlayerCharacter2::DropItems()
{
    if (ItemToDrop)
    {
        FVector SpawnLocation = GetActorLocation();
        SpawnLocation.Z = GetActorLocation().Z - 80.0f;

        ASItem* SpawnedItem = GetWorld()->SpawnActor<ASItem>(ItemToDrop, SpawnLocation, FRotator::ZeroRotator);

    }

}

void ASNonPlayerCharacter2::SpawnDragon()
{
    if (BossMonster)
    {
        FVector SpawnLocation = FVector(-4998.0f, -880.0f, 300.0f);
        FRotator SPawnRotator = FRotator(0.0f, 90.0f, 0.0f);

        ASMonster* SpawnedMonster = GetWorld()->SpawnActor<ASMonster>(BossMonster, SpawnLocation, SPawnRotator);
        
    }
}

void ASNonPlayerCharacter2::Attack()
{
    FHitResult HitResult;
    FCollisionQueryParams Params(NAME_None, false, this);

    bool bResult = GetWorld()->SweepSingleByChannel(
        HitResult,
        GetActorLocation(),
        GetActorLocation() + AttackRange * GetActorForwardVector(),
        FQuat::Identity,
        ECollisionChannel::ECC_EngineTraceChannel2,
        FCollisionShape::MakeSphere(AttackRadius),
        Params
    );

    if (true == bResult)
    {
        if (true == ::IsValid(HitResult.GetActor()))
        {
            UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("[NPC] Hit Actor Name: %s"), *HitResult.GetActor()->GetName()));
        }
    }

    USAnimInstance* AnimInstance = Cast<USAnimInstance>(GetMesh()->GetAnimInstance());
    if (true == ::IsValid(AnimInstance))
    {
        AnimInstance->PlayAttackAnimMontage();
        bIsAttacking = true;
        if (false == AnimInstance->OnMontageEnded.IsAlreadyBound(this, &ThisClass::OnAttackAnimMontageEnded))
        {
            AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnAttackAnimMontageEnded);
        }
    }

    if (true == bResult)
    {
        if (true == ::IsValid(HitResult.GetActor()))
        {
            ASCharacter* PlayerCharacter = Cast<ASCharacter>(HitResult.GetActor());
            if (true == ::IsValid(PlayerCharacter))
            {
                PlayerCharacter->TakeDamage(10.f, FDamageEvent(), GetController(), this);
            }
        }
    }


#pragma region CollisionDebugDrawing
    FVector TraceVec = GetActorForwardVector() * AttackRange;
    FVector Center = GetActorLocation() + TraceVec * 0.5f;
    float HalfHeight = AttackRange * 0.5f + AttackRadius;
    FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
    FColor DrawColor = true == bResult ? FColor::Green : FColor::Red;
    float DebugLifeTime = 5.f;

    DrawDebugCapsule(
        GetWorld(),
        Center,
        HalfHeight,
        AttackRadius,
        CapsuleRot,
        DrawColor,
        false,
        DebugLifeTime
    );
#pragma endregion
    
}

void ASNonPlayerCharacter2::OnAttackAnimMontageEnded(UAnimMontage* Montage, bool bIsInterrupt)
{
    bIsAttacking = false;
}
