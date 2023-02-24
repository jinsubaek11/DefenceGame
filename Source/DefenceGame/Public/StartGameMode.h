#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartGameMode.generated.h"

UCLASS()
class DEFENCEGAME_API AStartGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AStartGameMode();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> startUI;
	UPROPERTY()
	class UStartWidget* startUIWidget;
	

};
