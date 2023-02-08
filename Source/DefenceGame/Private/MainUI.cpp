#include "MainUI.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "DefenceGameMode.h"


void UMainUI::PrintBulletCount(int32 bulletCount, int32 maxBulletCount)
{
	CountText->SetText(FText::AsNumber(bulletCount));
	MaxCountText->SetText(FText::AsNumber(maxBulletCount));
}

void UMainUI::PrintItemRemainingTime(int32 remainingTime, int32 coolTime)
{
	CountText->SetText(FText::AsNumber(remainingTime));
	MaxCountText->SetText(FText::AsNumber(coolTime));
}

void UMainUI::SetCurrentWeaponImage(ADefenceGameMode* gameMode, WeaponType type)
{
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
	switch (type)
	{
	case ItemType::OBSTACLE:
		IconImage->SetBrushFromMaterial(gameMode->iconMats["obstacle"]);
		break;
	case ItemType::TURRET:
		IconImage->SetBrushFromMaterial(gameMode->iconMats["turret"]);
		break;
	}
}
