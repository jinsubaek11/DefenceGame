#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "characterHPWidget.generated.h"


UCLASS()
class DEFENCEGAME_API UcharacterHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void ShowHPBar(float hp, float maxHp);

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "characterHPSettings", meta = (BindWidget))
	class UProgressBar* charHPBar;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "characterHPSettings", meta = (BindWidget))
	class UTextBlock* charHPNum;
};
