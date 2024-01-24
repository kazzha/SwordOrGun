
#include "UI/SW_Bar.h"
#include "Components/ProgressBar.h"
#include "Characters/SNonPlayerCharacter2.h"
#include "Components/SStatComponent.h"

USW_Bar::USW_Bar(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void USW_Bar::SetMaxFigure(float InMaxFigure)
{
	if (InMaxFigure < KINDA_SMALL_NUMBER)
	{
		MaxFigure = 0.f;
		return;
	}

	MaxFigure = InMaxFigure;
}

void USW_Bar::NativeConstruct()
{
	Super::NativeConstruct();

	Bar = Cast<UProgressBar>(GetWidgetFromName("BarWidget"));
	// 하이어리키에서 이 이름의 위젯을 가져와서 바에 넣어주라는 뜻의 하드코딩 
	// == Meta = (BindWidget) 과 같은 효과

	check(nullptr != Bar);
}
