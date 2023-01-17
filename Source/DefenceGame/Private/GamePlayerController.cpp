#include "GamePlayerController.h"
#include "GamePlayerCameraManager.h"


AGamePlayerController::AGamePlayerController()
{
	PlayerCameraManagerClass = AGamePlayerCameraManager::StaticClass();
}