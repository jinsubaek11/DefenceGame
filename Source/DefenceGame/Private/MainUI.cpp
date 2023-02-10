#include "MainUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "DefenceGameMode.h"
#include "Components/VerticalBox.h"
#include "Components/Overlay.h"


void UMainUI::NativeConstruct()
{
	backgroundMat = Cast<UMaterialInterface>(BoxBG->Brush.GetResourceObject());
	if (backgroundMat)
	{
		dynamicBackgroundMat = UMaterialInstanceDynamic::Create(backgroundMat, this);
		BoxBG->SetBrushFromMaterial(dynamicBackgroundMat);
	}

	ItemBox->SetVisibility(ESlateVisibility::Hidden);
}

void UMainUI::PrintBulletCount(int32 bulletCount, int32 maxBulletCount)
{
	CountText->SetText(FText::AsNumber(bulletCount));
	MaxCountText->SetText(FText::AsNumber(maxBulletCount));
}

void UMainUI::PrintItemRemainingTime(float remainingTime, float coolTime)
{
	//dynamicBackgroundMat->SetMat
	dynamicBackgroundMat->SetScalarParameterValue(TEXT("Percent"), remainingTime / coolTime);
	RemainingTime->SetText(FText::AsNumber((int)remainingTime));
}

void UMainUI::SetCurrentWeaponImage(ADefenceGameMode* gameMode, WeaponType type)
{
	WeaponBox->SetVisibility(ESlateVisibility::Visible);
	ItemBox->SetVisibility(ESlateVisibility::Hidden);

	switch (type)
	{
	case WeaponType::RIFLE:
		IconImage->SetBrushFromMaterial(gameMode->iconMats["rifle"]);
		break;
	case WeaponType::BAZOOKA:
		IconImage->SetBrushFromMaterial(gameMode->iconMats["bazooka"]);
		break;
	case WeaponType::HAND_GRENADE:
		IconImage->SetBrushFromMaterial(gameMode->iconMats["grenade"]);
		break;
	}
}

void UMainUI::SetCurrentItemImage(ADefenceGameMode* gameMode, ItemType type)
{
	ItemBox->SetVisibility(ESlateVisibility::Visible);
	WeaponBox->SetVisibility(ESlateVisibility::Hidden);

	switch (type)
	{
	case ItemType::OBSTACLE:
		ItemImage->SetBrushFromMaterial(gameMode->iconMats["obstacle"]);
		break;
	case ItemType::TURRET:
		ItemImage->SetBrushFromMaterial(gameMode->iconMats["turret"]);
		break;
	}
}

