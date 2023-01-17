#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefenceGameMode.generated.h"


UCLASS()
class DEFENCEGAME_API ADefenceGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	void BeginPlay() override;

private:
};
