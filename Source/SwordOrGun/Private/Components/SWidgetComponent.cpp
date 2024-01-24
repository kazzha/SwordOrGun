#include "Components/SWidgetComponent.h"
#include "UI/SwordUserWidget.h"

void USWidgetComponent::InitWidget()
{
	Super::InitWidget();

	USwordUserWidget* SWidget = Cast<USwordUserWidget>(GetWidget());
	if (true == ::IsValid(SWidget))
	{
		SWidget->SetOwningActor(GetOwner());
	}
}
