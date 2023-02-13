#include "HPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UHPWidget::ShowHealthBar(float hp, float maxHp)
{
	towerHPBar->SetPercent(hp / maxHp);
	towerHPNum->SetText(FText::AsNumber(hp));
}
