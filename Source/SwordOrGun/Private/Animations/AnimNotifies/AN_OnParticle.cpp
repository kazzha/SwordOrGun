
#include "Animations/AnimNotifies/AN_OnParticle.h"
#include "Characters/STPSCharacter.h"

void UAN_OnParticle::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

    if (true == ::IsValid(MeshComp))
    {
        ASTPSCharacter* AttackingCharacter = Cast<ASTPSCharacter>(MeshComp->GetOwner());
        if (true == ::IsValid(AttackingCharacter) && PSTemplate)
        {
            LocationOffset.Y += 70.f;
            LocationOffset.Z += 10.f;
            SpawnParticleSystem(MeshComp, Animation);
        }
    }
}
