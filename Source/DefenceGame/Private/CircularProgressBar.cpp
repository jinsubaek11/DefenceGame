#include "CircularProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UCircularProgressBar::NativeConstruct()
{
	originalMaterial = Cast<UMaterialInterface>(ProgressBar->Brush.GetResourceObject());
	if (originalMaterial)
	{
		dynamicMaterial = UMaterialInstanceDynamic::Create(originalMaterial, this);
		ProgressBar->SetBrushFromMaterial(dynamicMaterial);
	}
}

void UCircularProgressBar::PrintCurrentHealth(int currentHp, int maxHp)
{
	float percent = (float)currentHp / maxHp;

	hpText->SetText(FText::AsNumber(currentHp));
	ProgressBar->GetDynamicMaterial()->SetScalarParameterValue(TEXT("Percent"), percent);
}

