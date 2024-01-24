#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SwordUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API USwordUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	AActor* GetOwningActor() const { return OwningActor; }

	void SetOwningActor(AActor* InOwningActor) { OwningActor = InOwningActor; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = USwordUserWidget)
	TObjectPtr<AActor> OwningActor;
};
