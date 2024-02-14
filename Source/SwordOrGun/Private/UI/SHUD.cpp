
#include "UI/SHUD.h"
#include "Components/SStatComponent.h"
#include "Game/SPlayerState.h"
#include "UI/SW_HPBar.h"
#include "UI/SW_EXPBar.h"
#include "Components/TextBlock.h"
#include "Game/SGameInstance.h"

void USHUD::BindStatComponent(USStatComponent* InStatComponent)
{
	if (true == ::IsValid(InStatComponent))
	{
		StatComponent = InStatComponent;
		StatComponent->OnCurrentHPChangeDelegate.AddDynamic(HPBar, &USW_HPBar::OnCurrentHPChange);
		StatComponent->OnMaxHPChangeDelegate.AddDynamic(HPBar, &USW_HPBar::OnMaxHPChange);
	}

	USGameInstance* GameInstance = Cast<USGameInstance>(GetWorld()->GetGameInstance());
	if (true == ::IsValid(GameInstance))
	{
		if (nullptr != GameInstance->GetCharacterStatDataTable() || nullptr != GameInstance->GetCharacterStatDataTableRow(1))
		{
			float MaxHP = GameInstance->GetCharacterStatDataTableRow(1)->MaxHP;
			HPBar->SetMaxHP(MaxHP);
			HPBar->InitializeHPBarWidget(StatComponent.Get());
			
		}
	}

	BossText->SetVisibility(ESlateVisibility::Collapsed);
}

void USHUD::BindPlayerState(ASPlayerState* InPlayerState)
{
	USGameInstance* GameInstance = Cast<USGameInstance>(GetWorld()->GetGameInstance());
	{	
		GameInstance->OnCurrentDeathCountDelegate.AddDynamic(this, &ThisClass::UpdateDeathCountText);
	}
	if (true == ::IsValid(InPlayerState))
	{
		PlayerState = InPlayerState;
		PlayerState->OnCurrentEXPChangedDelegate.AddDynamic(EXPBar, &USW_EXPBar::OnCurrentEXPChange);
		PlayerState->OnCurrentLevelChangedDelegate.AddDynamic(this, &ThisClass::UpdateLevelText);
		
		PlayerNameText->SetText(FText::FromString(PlayerState->GetPlayerName()));
		EXPBar->SetMaxEXP(PlayerState->GetMaxEXP());
		EXPBar->InitializeEXPBarWidget(PlayerState.Get());
		UpdateLevelText(0, PlayerState->GetCurrentLevel());
		UpdateDeathCountText(GameInstance->GetDeathCount());
	}
}

void USHUD::UpdateLevelText(int32 InOldLevel, int32 InNewLevel)
{
	FString LevelString = FString::Printf(TEXT("%d"), InNewLevel);

	LevelText->SetText(FText::FromString(LevelString));
}

void USHUD::UpdateDeathCountText(int32 InNewCount)
{
	
	FString DeathString = FString::Printf(TEXT("%d"), InNewCount);

	DeathCount->SetText(FText::FromString(DeathString));

	if (InNewCount == 7)
	{
		DeathCount->SetVisibility(ESlateVisibility::Collapsed);
		DeathText->SetVisibility(ESlateVisibility::Collapsed);
		BossText->SetVisibility(ESlateVisibility::Visible);
	}

}


