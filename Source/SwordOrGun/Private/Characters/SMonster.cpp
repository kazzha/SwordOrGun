
#include "Characters/SMonster.h"
#include "Components/CapsuleComponent.h"
#include "Components/SStatComponent.h"
#include "Components/SWidgetComponent.h"
#include "UI/SwordUserWidget.h"
#include "UI/SW_HPBar.h"
#include "Game/SPlayerState.h"
#include "Engine/EngineTypes.h"
#include "Engine/DamageEvents.h"
#include "Controllers/SAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Animations/SDragonAnimInstance.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_Sight.h"


ASMonster::ASMonster()
{
    PrimaryActorTick.bCanEverTick = false;

    AIControllerClass = ASAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

    float CharacterHalfHeight = 230.f;
    float CharacterRadius = 190.f;

    FVector PivotPosition(0.f, 0.f, CharacterHalfHeight);

    GetMesh()->SetRelativeLocation(PivotPosition);

    GetCapsuleComponent()->InitCapsuleSize(CharacterRadius, CharacterHalfHeight);
    // 폰 아래 클래스부터는 캡슐 컴포넌트를 부를 때 게터 사용

    WidgetComponent = CreateDefaultSubobject<USWidgetComponent>(TEXT("WidgetComponent"));
    WidgetComponent->SetupAttachment(GetRootComponent());
    WidgetComponent->SetRelativeLocation(FVector(0.f, 0.f, 300.f));
    WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    WidgetComponent->SetDrawSize(FVector2D(250.0f, 50.0f));
    WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    AIStimuliSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
    AIStimuliSource->bAutoRegister = true;

    AIStimuliSource->RegisterForSense(UAISense_Sight::StaticClass());
    AIStimuliSource->RegisterWithPerceptionSystem();
}

void ASMonster::BeginPlay()
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

    USDragonAnimInstance* AnimInstance = Cast<USDragonAnimInstance>(GetMesh()->GetAnimInstance());
    if (true == ::IsValid(AnimInstance) && false ==
        AnimInstance->OnMontageEnded.IsAlreadyBound(this, &ThisClass::OnAttackAnimMontageEnded))
    {
        AnimInstance->OnMontageEnded.AddDynamic(this, &ThisClass::OnAttackAnimMontageEnded);
        AnimInstance->PlayBeginPlayAnimMontage();
    }

}

float ASMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float FinalDamageAmount = Super::TakeDamage(Damage-40, DamageEvent, EventInstigator, DamageCauser);

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
                    PS->SetCurrentEXP(PS->GetCurrentEXP() + 100.f);
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

void ASMonster::SetWidget(USwordUserWidget* InSwordUserWidget)
{
    USW_HPBar* HPBarWidget = Cast<USW_HPBar>(InSwordUserWidget);
    if (true == ::IsValid(HPBarWidget))
    {
        HPBarWidget->SetMaxHP(StatComponent->GetMaxHP());
        HPBarWidget->InitializeHPBarWidget(StatComponent);
        StatComponent->OnCurrentHPChangeDelegate.AddDynamic(HPBarWidget, &USW_HPBar::OnCurrentHPChange);
    }
}

void ASMonster::Attack()
{
    FHitResult HitResult;
    FCollisionQueryParams Params(NAME_None, false, this);
    FVector ActorLocation = GetActorLocation();
    FVector ActorForwardVector = GetActorForwardVector();
    bool bResult = GetWorld()->SweepSingleByChannel(
        HitResult,
        ActorLocation,
        ActorLocation + AttackRange * GetActorForwardVector(),
        FQuat::Identity,
        ECollisionChannel::ECC_EngineTraceChannel2,
        FCollisionShape::MakeSphere(AttackRadius),
        Params
    );

    if (true == bResult)
    {
        if (true == ::IsValid(HitResult.GetActor()))
        {
           // UKismetSystemLibrary::PrintString(this, FString::Printf(TEXT("[NPC] Hit Actor Name: %s"), *HitResult.GetActor()->GetName()));
        }
    }

    USDragonAnimInstance* AnimInstance = Cast<USDragonAnimInstance>(GetMesh()->GetAnimInstance());
    if (true == ::IsValid(AnimInstance))
    {
        FMath::RandRange(0, 1) == 0 ? AnimInstance->PlaythrowAnimMontage() : AnimInstance->PlayFireAnimMontage();
        
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
                PlayerCharacter->TakeDamage(30.f, FDamageEvent(), GetController(), this);
            }
        }
    }

    /*
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
*/
}

void ASMonster::OnAttackAnimMontageEnded(UAnimMontage* Montage, bool bIsInterrupt)
{
    bIsAttacking = false;
}
