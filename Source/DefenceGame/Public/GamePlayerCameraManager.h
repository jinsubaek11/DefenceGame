#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "GamePlayerCameraManager.generated.h"


UCLASS()
class DEFENCEGAME_API AGamePlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()
	
public:
	AGamePlayerCameraManager();

};
