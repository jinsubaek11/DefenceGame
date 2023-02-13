#include "WarningBossWidget.h"
#include "Components/TextBlock.h"


void UWarningBossWidget::PrintWarningBossText(FString stage, FString method)
{
	
	stageText->SetText(FText::FromString(stage));
	methodText->SetText(FText::FromString(method));
}
