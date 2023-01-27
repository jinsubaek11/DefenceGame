#include "DefenceGameMode.h"
#include "kismet/GameplayStatics.h"
#include "ScreenBeforeGameStart.h"
#include "Components/WidgetComponent.h"



void ADefenceGameMode::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

	sbgs = CreateWidget<UScreenBeforeGameStart>(GetWorld(), screenBeforGameStart);
	
	sbgs->AddToViewport();
	sbgs->ShowStartGameText();
	sbgs->ShowStartTextBackground();

	FTimerHandle titleEndTime;
	GetWorld()->GetTimerManager().SetTimer(titleEndTime, this, &ADefenceGameMode::HideUI, 1.0f, false, 4.0f);

	UE_LOG(LogTemp, Warning, TEXT("Timer Handle"));
}

void ADefenceGameMode::HideUI()
{
	sbgs->RemoveFromParent();
}

