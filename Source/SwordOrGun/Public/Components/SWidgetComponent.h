#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "SWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API USWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	virtual void InitWidget() override;
};
