#include "DefenceGameMode.h"
#include "kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "ScreenBeforeGameStart.h"
#include "Components/WidgetComponent.h"
#include "MainUI.h"
#include "WarningBossWidget.h"
#include "GameOverWidget.h"
#include "TimerWidget.h"
#include "StageWidget.h"
#include "VictoryWidget.h"
#include "EngineUtils.h"
#include "EnemySpawner.h"
#include "BossSpawner.h"
#include "GamePlayer.h"
#include "Weapon.h"


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
	stageMethodTexts = { "", "Only Use Bazooka", "Only Use Rifle" };
}

void ADefenceGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(stageTimer, this, &ADefenceGameMode::PrintStageRemainingTime, 1.f, true);

	mainUIWidget = Cast<UMainUI>(CreateWidget(GetWorld(), mainUI));

	if (mainUIWidget)
	{
		mainUIWidget->AddToViewport();
	}

	warningBossWidget = Cast<UWarningBossWidget>(CreateWidget(GetWorld(), warningBossUI));
	//GetWorldTimerManager().SetTimer(bossAppearTimer, this, &ADefenceGameMode::ShowWarningBossScreen, 3.f, false);

	gameOverWidget = Cast<UGameOverWidget>(CreateWidget(GetWorld(), gameOverUI));
	victoryWidget = Cast<UVictoryWidget>(CreateWidget(GetWorld(), victoryUI));
	stageWidget = Cast<UStageWidget>(CreateWidget(GetWorld(), stageUI));

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

	screenBeforGameStart = CreateWidget<UScreenBeforeGameStart>(GetWorld(), screenBeforGameStartUI);
	if (screenBeforGameStart)
	{
		screenBeforGameStart->AddToViewport();
		screenBeforGameStart->ShowStartGameText();
		screenBeforGameStart->ShowStartTextBackground();
	}

	FTimerHandle titleEndTime;
	GetWorld()->GetTimerManager().SetTimer(titleEndTime, this, &ADefenceGameMode::HideScreenBeforGameStart, 2.0f, false);

	for (TActorIterator<AEnemySpawner> iter(GetWorld()); iter; ++iter)
	{
		enemySpawners.Emplace(*iter);
	}

	bossSpawner = GetWorld()->SpawnActor<ABossSpawner>();
	SetBossSpawnerLocation();
}

void ADefenceGameMode::ShowWarningBossScreen(FString stageText, FString methodText)
{
	if (warningBossWidget)
	{
		warningBossWidget->AddToViewport();
		warningBossWidget->PrintWarningBossText(stageText, methodText);
		
		bossSpawner->SpawnBoss();
	}

	AGamePlayer* player = Cast<AGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (player)
	{
		player->SetAttackMode(true);
		player->OnActionReleased();
		player->SetIsShoot(false);

		if (stage == 2)
		{
			player->OnActionSwitchWeapon((int)WeaponType::BAZOOKA);
		}
		else
		{
			player->OnActionSwitchWeapon((int)WeaponType::RIFLE);
		}
	}

	bossHandicap = true;

	FTimerHandle timer;
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([this] {
		//GetWorldTimerManager().ClearTimer(bossAppearTimer);
		warningBossWidget->RemoveFromParent();
	});

	GetWorldTimerManager().SetTimer(timer, timerDelegate, 2.f, false);
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

void ADefenceGameMode::HideScreenBeforGameStart()
{
	if (!screenBeforGameStart) return;

	screenBeforGameStart->RemoveFromParent();
	ShowStageScreen(stageTexts[stage - 1]);
}

void ADefenceGameMode::PrintStageRemainingTime()
{
	if (remainingTime < 0)
	{
		GetWorldTimerManager().ClearTimer(stageTimer);
		UpgradeStage();

		return;
	}

	if (stage > 1 && remainingTime == 60)
	//if (stage > 1 && remainingTime == 5)
	{
		ShowWarningBossScreen(stageTexts[stage - 1], stageMethodTexts[stage - 1]);
	}

	mainUIWidget->Timer->PrintTime(remainingTime);
	remainingTime--;
}

void ADefenceGameMode::UpgradeStage()
{
	if (stage >= maxStage)
	{
		ShowVictoryScreen();
		return;
	}

	SetBossSpawnerLocation();

	for (AEnemySpawner* spawner : enemySpawners)
	{
		spawner->ResetSpawn();
	}

	bossSpawner->ResetSpawn();

	bossHandicap = false;
	stage++;
	ShowStageScreen(stageTexts[stage - 1]);
	remainingTime = 90;
	//remainingTime = 10;
	GetWorldTimerManager().SetTimer(stageTimer, this, &ADefenceGameMode::PrintStageRemainingTime, 1.f, true);
}

void ADefenceGameMode::ShowStageScreen(FString stageText)
{
	if (!stageWidget) return;
	stageWidget->AddToViewport();
	stageWidget->PrintStage(stageText);

	FTimerHandle timer;
	FTimerDelegate timerDelegate;
	timerDelegate.BindLambda([this] {
		stageWidget->RemoveFromParent();
		//ShowVictoryScreen();

	});

	GetWorldTimerManager().SetTimer(timer, timerDelegate, 2.f, false);
}

void ADefenceGameMode::ShowVictoryScreen()
{
	if (!victoryWidget) return;

	victoryWidget->AddToViewport();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true);
}

bool ADefenceGameMode::HasHandicap() const
{
	return bossHandicap;
}

void ADefenceGameMode::SetBossSpawnerLocation()
{
	int32 random = FMath::RandRange(0, 3);

	UE_LOG(LogTemp, Warning, TEXT("%s"), *enemySpawners[random]->GetActorLocation().ToString());

	bossSpawner->SetActorLocation(enemySpawners[random]->GetActorLocation());
}

