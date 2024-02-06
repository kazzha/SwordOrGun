#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify_PlayParticleEffect.h"
#include "AN_OnParticle.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API UAN_OnParticle : public UAnimNotify_PlayParticleEffect
{
	GENERATED_BODY()

	void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
	
};
