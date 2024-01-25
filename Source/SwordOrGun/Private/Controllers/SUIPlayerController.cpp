
#include "Controllers/SUIPlayerController.h"
#include "Blueprint/UserWidget.h"

void ASUIPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (true == ::IsValid(UIWidgetClass))
	{
		UIWidgetInstance = CreateWidget<UUserWidget>(this, UIWidgetClass);
		if (true == ::IsValid(UIWidgetInstance))
		{
			UIWidgetInstance->AddToViewport(); 

			FInputModeUIOnly Mode;
			Mode.SetWidgetToFocus(UIWidgetInstance->GetCachedWidget());
			SetInputMode(Mode);

			bShowMouseCursor = true;
		}
	}
}
