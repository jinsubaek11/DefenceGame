#include "DefenceGameMode.h"
#include "kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "ScreenBeforeGameStart.h"
#include "Components/WidgetComponent.h"


ADefenceGameMode::ADefenceGameMode()
{

}

void ADefenceGameMode::BeginPlay()
{
	Super::BeginPlay();

	rifleCrossHairWidget = CreateWidget(GetWorld(), rifleCrossHair);
	rifleCrossHairWidget->AddToViewport();
	//UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));

	sbgs = CreateWidget<UScreenBeforeGameStart>(GetWorld(), screenBeforGameStart);
	if (sbgs)
	{
		sbgs->AddToViewport();
		sbgs->ShowStartGameText();
		sbgs->ShowStartTextBackground();
	}

	FTimerHandle titleEndTime;
	GetWorld()->GetTimerManager().SetTimer(titleEndTime, this, &ADefenceGameMode::HideUI, 1.0f, false, 4.0f);

	UE_LOG(LogTemp, Warning, TEXT("Timer Handle"));
}

void ADefenceGameMode::HideUI()
{
	sbgs->RemoveFromParent();
}

