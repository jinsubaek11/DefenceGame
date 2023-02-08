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
	void HideUI();
	void ShowGameOverScreen();
	void ShowWarningBossScreen();

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
	TSubclassOf<class UScreenBeforeGameStart> screenBeforGameStart;
	UPROPERTY()
	class UScreenBeforeGameStart* sbgs;

	TMap<FString, UMaterialInterface*> iconMats;
	TArray<FString> stageTexts;

	FTimerHandle bossAppearTimer;
};
