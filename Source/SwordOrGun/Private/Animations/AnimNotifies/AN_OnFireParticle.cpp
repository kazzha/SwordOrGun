
#include "Animations/AnimNotifies/AN_OnFireParticle.h"
#include "Characters/SMonster.h"

void UAN_OnFireParticle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
    Super::Notify(MeshComp, Animation, EventReference);

    SocketName = TEXT("Fire");

    if (true == ::IsValid(MeshComp))
    {
        ASMonster* AttackingMonster = Cast<ASMonster>(MeshComp->GetOwner());
        if (true == ::IsValid(AttackingMonster) && PSTemplate)
        {
            SpawnParticleSystem(MeshComp, Animation);
        }
    }
}
