#include "StageWidget.h"
#include "Components/TextBlock.h"


void UStageWidget::PrintStage(FString stage)
{
	StageText->SetText(FText::FromString(stage));
}
