#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SHUD.generated.h"

/**
 * 
 */
UCLASS()
class SWORDORGUN_API USHUD : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindStatComponent(class USStatComponent* InStatComponent);

	void BindPlayerState(class ASPlayerState* InPlayerState);

protected:
	UFUNCTION()
	virtual void UpdateLevelText(int32 InOldLevel, int32 InNewLevel);

	UFUNCTION()
	virtual void UpdateDeathCountText(int32 InNewCount);

protected:
	TWeakObjectPtr<class USStatComponent> StatComponent;

	TWeakObjectPtr<class ASPlayerState> PlayerState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "USHUD", Meta = (BindWidget))
	TObjectPtr<class UTextBlock> LevelText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "USHUD", Meta = (BindWidget))
	TObjectPtr<class UTextBlock> PlayerNameText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "USHUD", Meta = (BindWidget))
	TObjectPtr<class USW_HPBar> HPBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "USHUD", Meta = (BindWidget))
	TObjectPtr<class USW_EXPBar> EXPBar;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "USHUD", Meta = (BindWidget))
	TObjectPtr<class UTextBlock> DeathCount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "USHUD", Meta = (BindWidget))
	TObjectPtr<class UTextBlock> DeathText;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "USHUD", Meta = (BindWidget))
	TObjectPtr<class UTextBlock> BossText;

};
