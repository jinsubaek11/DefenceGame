#include "DefenceGameMode.h"
#include "kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"


ADefenceGameMode::ADefenceGameMode()
{

}

void ADefenceGameMode::BeginPlay()
{
	Super::BeginPlay();

	rifleCrossHairWidget = CreateWidget(GetWorld(), rifleCrossHair);
	rifleCrossHairWidget->AddToViewport();
}
