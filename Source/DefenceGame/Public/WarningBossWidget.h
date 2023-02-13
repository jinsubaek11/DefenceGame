#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WarningBossWidget.generated.h"


UCLASS()
class DEFENCEGAME_API UWarningBossWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void PrintWarningBossText(FString stage, FString method = "");

private:
	UPROPERTY(EditDefaultsOnly, meta = (bindwidget))
	class UTextBlock* methodText;
	UPROPERTY(EditDefaultsOnly, meta = (bindwidget))
	class UTextBlock* stageText;
};
