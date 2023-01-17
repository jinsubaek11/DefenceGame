#include "DefenceGameMode.h"
#include "kismet/GameplayStatics.h"


void ADefenceGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

}
