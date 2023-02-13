#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StageWidget.generated.h"


UCLASS()
class DEFENCEGAME_API UStageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void PrintStage(FString stage);

public:
	UPROPERTY(EditDefaultsOnly, meta = (bindwidget))
	class UTextBlock* StageText;
};
