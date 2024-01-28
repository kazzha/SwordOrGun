
#include "Characters/STPSNonPlayerCharacter.h"
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
#include "Camera/CameraComponent.h"


ASTPSNonPlayerCharacter::ASTPSNonPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    AIControllerClass = ASAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    CameraComponent->SetRelativeLocation(FVector(0.f, 60.f, 20.f));

    WidgetComponent = CreateDefaultSubobject<USWidgetComponent>(TEXT("WidgetComponent"));
    WidgetComponent->SetupAttachment(GetRootComponent());
    WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
    WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    WidgetComponent->SetDrawSize(FVector2D(200.0f, 50.0f));
    WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    WeaponSkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponSkeletalMeshComponent"));
}

void ASTPSNonPlayerCharacter::BeginPlay()
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

    FName EquipmentSocketName = FName(TEXT("EquipmentSocket"));
    if (true == GetMesh()->DoesSocketExist(EquipmentSocketName))
    {
        WeaponSkeletalMeshComponent->AttachToComponent(GetMesh(),
            FAttachmentTransformRules::SnapToTargetIncludingScale, EquipmentSocketName);

    }
}

float ASTPSNonPlayerCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float FinalDamageAmount = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

    if (StatComponent->GetCurrentHP() < KINDA_SMALL_NUMBER)
    {
        if (true == ::IsValid(LastHitBy))
        {
            ASCharacter* DamageCauserCharacter = Cast<ASCharacter>(LastHitBy->GetPawn());
            if (true == ::IsValid(DamageCauserCharacter))
            {
                ASPlayerState* PS = Cast<ASPlayerState>(DamageCauserCharacter->GetPlayerState());
                if (true == ::IsValid(PS))
                {
                    PS->SetCurrentEXP(PS->GetCurrentEXP() + 20.f);
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

void ASTPSNonPlayerCharacter::SetWidget(USwordUserWidget* InSwordUserWidget)
{
    USW_HPBar* HPBarWidget = Cast<USW_HPBar>(InSwordUserWidget);
    if (true == ::IsValid(HPBarWidget))
    {
        HPBarWidget->SetMaxHP(StatComponent->GetMaxHP());
        HPBarWidget->InitializeHPBarWidget(StatComponent);
        StatComponent->OnCurrentHPChangeDelegate.AddDynamic(HPBarWidget, &USW_HPBar::OnCurrentHPChange);
    }
}

void ASTPSNonPlayerCharacter::Attack()
{

    FHitResult HitResult;

    FVector CameraStartLocation = CameraComponent->GetComponentLocation();
    FVector CameraEndLocation = CameraStartLocation + CameraComponent->GetForwardVector() * 5000.f;

    FCollisionQueryParams QueryParams;
    QueryParams.AddIgnoredActor(this);
    QueryParams.AddIgnoredComponent((const UPrimitiveComponent*)(CameraComponent));
    QueryParams.bTraceComplex = true;

    FVector MuzzleLocation = WeaponSkeletalMeshComponent->GetSocketLocation(FName("MussleSocket"));
    bool bIsCollide = GetWorld()->LineTraceSingleByChannel(HitResult, MuzzleLocation, CameraEndLocation,
        ECC_Visibility, QueryParams);

    if (true == bIsCollide)
    {
        DrawDebugLine(GetWorld(), MuzzleLocation, HitResult.Location, FColor(255, 255, 255, 64), true, 0.1f, 0U, 0.5f);

        ASCharacter* HittedCharacter = Cast<ASCharacter>(HitResult.GetActor());
        if (true == ::IsValid(HittedCharacter))
        {
            FDamageEvent DamageEvent;
            HittedCharacter->TakeDamage(10.f, DamageEvent, GetController(), this);
        }
    }
    else
    {
        DrawDebugLine(GetWorld(), MuzzleLocation, CameraEndLocation, FColor(255, 255, 255, 64), false, 0.1f, 0U, 0.5f);
    }

    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (false == ::IsValid(AnimInstance))
    {
        return;
    }
    if (false == AnimInstance->Montage_IsPlaying(RifleFireAnimMontage))
    {
        AnimInstance->Montage_Play(RifleFireAnimMontage);
    }
   
}

void ASTPSNonPlayerCharacter::OnAttackAnimMontageEnded(UAnimMontage* Montage, bool bIsInterrupt)
{
}
