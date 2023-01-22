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
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> rifleCrossHair;
	UPROPERTY()
	class UUserWidget* rifleCrossHairWidget;
};
