#include "TimerWidget.h"
#include "Components/TextBlock.h"


void UTimerWidget::PrintTime(int32 time)
{
	float minute = time / 60;
	float second = time % 60;

	FString minuteStr = FString::FromInt(minute);
	FString secondStr = second <= 9 ? "0" + FString::FromInt(second) : FString::FromInt(second);

	TimerText->SetText(FText::FromString(minuteStr + " : " + secondStr));
}
