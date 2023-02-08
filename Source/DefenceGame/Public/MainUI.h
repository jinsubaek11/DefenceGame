#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Item.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"


UCLASS()
class DEFENCEGAME_API UMainUI : public UUserWidget
{
	GENERATED_BODY()

public:
	void PrintBulletCount(int32 bulletCount, int32 maxBulletCount);
	void PrintItemRemainingTime(int32 remainingTime, int32 coolTime);
	void SetCurrentWeaponImage(class ADefenceGameMode* gameMode, WeaponType type);
	void SetCurrentItemImage(class ADefenceGameMode* gameMode, ItemType type);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UTextBlock* CountText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UTextBlock* MaxCountText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UCircularProgressBar* HealthBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UImage* IconImage;

	UPROPERTY()
	class UMaterialInterface* rifleMat;
	UPROPERTY()
	class UMaterialInterface* bazookaMat;
	UPROPERTY()
	class UMaterialInterface* grenadeMat;
	UPROPERTY()
	class UMaterialInterface* obstacleMat;
	UPROPERTY()
	class UMaterialInterface* turretMat;



	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	//class UTextBlock* ;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	//class UTextBlock* BulletCount;

};
