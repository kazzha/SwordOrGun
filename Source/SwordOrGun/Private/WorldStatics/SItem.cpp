
#include "WorldStatics/SItem.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

ASItem::ASItem()
{
    PrimaryActorTick.bCanEverTick = false;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    SetRootComponent(BoxComponent);
    BoxComponent->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ASItem::OnOverlapBegin);
    BoxComponent->SetCollisionProfileName(FName(TEXT("SItemBox")));

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    StaticMeshComponent->SetupAttachment(GetRootComponent());
    StaticMeshComponent->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));
    StaticMeshComponent->SetCollisionProfileName(TEXT("NoCollision"));
   

    ParticleSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystemComponent"));
    ParticleSystemComponent->SetupAttachment(GetRootComponent());
    ParticleSystemComponent->SetAutoActivate(false);
    

}

void ASItem::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
    ParticleSystemComponent->Activate(true);
    StaticMeshComponent->SetHiddenInGame(true);
    SetActorEnableCollision(false);
    ParticleSystemComponent->OnSystemFinished.AddDynamic(this, &ASItem::OnEffectFinish);
}

void ASItem::OnEffectFinish(UParticleSystemComponent* ParticleSystem)
{
    Destroy();
}
