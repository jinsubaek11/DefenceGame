#include "DefenceGameMode.h"
#include "kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "ScreenBeforeGameStart.h"
#include "Components/WidgetComponent.h"
#include "MainUI.h"
#include "WarningBossWidget.h"
#include "GameOverWidget.h"


ADefenceGameMode::ADefenceGameMode()
{
	ConstructorHelpers::FObjectFinder<UMaterialInterface> rifle(TEXT("/Script/Engine.Material'/Game/UI/Image/M_Rifle.M_Rifle'"));
	if (rifle.Succeeded())
	{
		iconMats.Add({ "rifle", rifle.Object });
	}

	ConstructorHelpers::FObjectFinder<UMaterialInterface> bazooka(TEXT("/Script/Engine.Material'/Game/UI/Image/M_Bazooka.M_Bazooka'"));
	if (bazooka.Succeeded())
	{
		iconMats.Add({ "bazooka", bazooka.Object });
	}

	ConstructorHelpers::FObjectFinder<UMaterialInterface> grenade(TEXT("/Script/Engine.Material'/Game/UI/Image/M_Grenade.M_Grenade'"));
	if (grenade.Succeeded())
	{
		iconMats.Add({ "grenade", grenade.Object });
	}

	ConstructorHelpers::FObjectFinder<UMaterialInterface> obstacle(TEXT("/Script/Engine.Material'/Game/UI/Image/M_WoodBoard.M_WoodBoard'"));
	if (obstacle.Succeeded())
	{
		iconMats.Add({ "obstacle", obstacle.Object });
	}

	ConstructorHelpers::FObjectFinder<UMaterialInterface> turret(TEXT("/Script/Engine.Material'/Game/UI/Image/M_Turret.M_Turret'"));
	if (turret.Succeeded())
	{
		iconMats.Add({ "turret", turret.Object });
	}

	stageTexts = { "Fisrt", "Second", "Third" };
}

void ADefenceGameMode::BeginPlay()
{
	Super::BeginPlay();

	mainUIWidget = Cast<UMainUI>(CreateWidget(GetWorld(), mainUI));

	if (mainUIWidget)
	{
		mainUIWidget->AddToViewport();
	}

	warningBossWidget = Cast<UWarningBossWidget>(CreateWidget(GetWorld(), warningBossUI));
	//GetWorldTimerManager().SetTimer(bossAppearTimer, this, &ADefenceGameMode::ShowWarningBossScreen, 3.f, false);

	gameOverWidget = Cast<UGameOverWidget>(CreateWidget(GetWorld(), gameOverUI));

	rifleCrossHairWidget = CreateWidget(GetWorld(), rifleCrossHair);
	if (rifleCrossHairWidget)
	{
		rifleCrossHairWidget->AddToViewport();
	}

	miniMapWidget = CreateWidget(GetWorld(), miniMap);
	if (miniMapWidget)
	{
		miniMapWidget->AddToViewport();
	}
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

void ADefenceGameMode::ShowWarningBossScreen()
{
	if (warningBossWidget)
	{
		warningBossWidget->AddToViewport();
	}

	FTimerHandle timer;
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([this] {
		GetWorldTimerManager().ClearTimer(bossAppearTimer);
		warningBossWidget->RemoveFromParent();
	});

	GetWorldTimerManager().SetTimer(timer, timerDelegate, 3.f, false);
}

void ADefenceGameMode::ShowGameOverScreen()
{
	if (gameOverWidget)
	{
		gameOverWidget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
	}
}

void ADefenceGameMode::HideUI()
{
	sbgs->RemoveFromParent();
}

