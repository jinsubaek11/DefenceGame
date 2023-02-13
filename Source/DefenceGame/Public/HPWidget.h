#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPWidget.generated.h"


UCLASS()
class DEFENCEGAME_API UHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ShowHealthBar(float hp, float maxHp);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HPWidgetSettings", meta = (BindWidget))
	class UProgressBar* towerHPBar;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HPWidgetSettings", meta = (BindWidget))
	class UTextBlock* towerHPNum;
};
