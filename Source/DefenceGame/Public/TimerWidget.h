#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"


UCLASS()
class DEFENCEGAME_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void PrintTime(int32 time);

public:
	UPROPERTY(EditDefaultsOnly, meta = (bindwidget))
	class UTextBlock* TimerText;
};
