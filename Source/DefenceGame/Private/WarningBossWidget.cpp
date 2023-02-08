#include "WarningBossWidget.h"
#include "Components/TextBlock.h"


void UWarningBossWidget::PrintWarningBossText(FString method, FString stage)
{
	
	methodText->SetText(FText::FromString(method));
	stageText->SetText(FText::FromString(stage));
}
