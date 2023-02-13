#include "characterHPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UcharacterHPWidget::ShowHPBar(float hp, float maxHp)
{
	charHPBar->SetPercent(hp / maxHp);
	charHPNum->SetText(FText::AsNumber(hp));
}


