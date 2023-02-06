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

	class UScreenBeforeGameStart* sbgs;


	void HideUI();
};
