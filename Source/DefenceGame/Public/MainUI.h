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
	virtual void NativeConstruct() override;

public:
	void PrintBulletCount(int32 bulletCount, int32 maxBulletCount);
	void PrintItemRemainingTime(float remainingTime, float coolTime);
	void ClearItemRemainingTime();
	void SetCurrentWeaponImage(class ADefenceGameMode* gameMode, WeaponType type);
	void SetCurrentItemImage(class ADefenceGameMode* gameMode, ItemType type);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UTextBlock* CountText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UTextBlock* MaxCountText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UCircularProgressBar* HealthProgressBar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UImage* IconImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UImage* ItemImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UImage* BoxBG;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UVerticalBox* WeaponBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UOverlay* ItemBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UTextBlock* RemainingTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UTimerWidget* Timer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	class UHPWidget* BoxHP;

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

	UPROPERTY()
	class UMaterialInterface* backgroundMat;
	UPROPERTY()
	class UMaterialInstanceDynamic* dynamicBackgroundMat;


	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	//class UTextBlock* ;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MySetting", meta = (BindWidget))
	//class UTextBlock* BulletCount;

};
