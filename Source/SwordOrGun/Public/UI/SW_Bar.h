#pragma once

#include "CoreMinimal.h"
#include "UI/SwordUserWidget.h"
#include "SW_Bar.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API USW_Bar : public USwordUserWidget
{
	GENERATED_BODY()
public:
	USW_Bar(const FObjectInitializer& ObjectInitializer);

	void SetMaxFigure(float InMaxFigure);

protected:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "USW_Bar")
	TObjectPtr<class UProgressBar> Bar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "USW_Bar")
	float MaxFigure;
};
