#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefenceGameMode.generated.h"


UCLASS()
class DEFENCEGAME_API ADefenceGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADefenceGameMode();

protected:
	void BeginPlay() override;

public:
	void HideScreenBeforGameStart();
	void ShowStageScreen(FString stageText);
	void ShowVictoryScreen();
	void ShowGameOverScreen();
	void ShowWarningBossScreen(FString stageText, FString methodText = "");
	void PrintStageRemainingTime();

	bool HasHandicap() const;

private:
	void UpgradeStage();
	void SetBossSpawnerLocation();

public:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> mainUI;
	UPROPERTY()
	class UMainUI* mainUIWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> warningBossUI;
	UPROPERTY()
	class UWarningBossWidget* warningBossWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> victoryUI;
	UPROPERTY()
	class UVictoryWidget* victoryWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> stageUI;
	UPROPERTY()
	class UStageWidget* stageWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> gameOverUI;
	UPROPERTY()
	class UGameOverWidget* gameOverWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> rifleCrossHair;
	UPROPERTY()
	class UUserWidget* rifleCrossHairWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> miniMap;
	UPROPERTY()
	class UUserWidget* miniMapWidget;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class UUserWidget> screenBeforGameStartUI;
	UPROPERTY()
	class UScreenBeforeGameStart* screenBeforGameStart;

	TMap<FString, UMaterialInterface*> iconMats;
	TArray<FString> stageTexts;
	TArray<FString> stageMethodTexts;
	int32 stage = 1;
	int32 maxStage = 3;

	bool bossHandicap;

	FTimerHandle bossAppearTimer;
	FTimerHandle stageTimer;
	int32 remainingTime = 60;
	//int32 remainingTime = 5;

private:
	TArray<class AEnemySpawner*> enemySpawners;
	class ABossSpawner* bossSpawner;
};

