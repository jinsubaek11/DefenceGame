#include "Tower.h"
#include "EnemyAxe.h"
#include "FatalTeeth.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "HPWidget.h"
#include "Blueprint/UserWidget.h"
#include "Camera/PlayerCameraManager.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "DefenceGameMode.h"
#include "MainUI.h"


ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	boxComponent->SetBoxExtent(FVector(165, 180, 190));
	boxComponent->SetCollisionProfileName(TEXT("TowerPreset"));
	SetRootComponent(boxComponent);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Game/Asian_Village/meshes/building/SM_tower_02.SM_tower_02'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetRelativeScale3D(FVector(14));
		meshComponent->SetRelativeLocation(FVector(0, -16, 40));
		meshComponent->SetupAttachment(RootComponent);
	}

	towerHPui = CreateDefaultSubobject<UWidgetComponent>(TEXT("towerHPui"));
	towerHPui->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	towerHPui->SetRelativeLocationAndRotation(FVector(-4, -4, 238), FRotator(0, 90, 0));
	towerHPui->SetWidgetSpace(EWidgetSpace::Screen);
	

	ConstructorHelpers::FClassFinder<UUserWidget> hpwidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/BP_HPWidget'"));

	if (hpwidget.Succeeded())
	{
		towerHPui->SetWidgetClass(hpwidget.Class);
		towerHPui->SetDrawSize(FVector2D(250, 40));
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATower::OnOverlap);

	gameMode = Cast<ADefenceGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode && gameMode->mainUIWidget)
	{
		gameMode->mainUIWidget->BoxHP->ShowHealthBar(towerHP, towerMaxHP);
	}

	chpWidget = Cast<UHPWidget>(towerHPui->GetWidget());

	if (chpWidget)
	{
		chpWidget->ShowHealthBar(towerHP, towerMaxHP);
	}
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto cm = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	if (cm)
	{
		FRotator newRotation = UKismetMathLibrary::MakeRotFromXZ(
			cm->GetCameraLocation() - GetActorLocation(), GetActorUpVector()
		);

		towerHPui->SetWorldRotation(newRotation);
	}
}

void ATower::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ATower::OnTakeDamage(float attack)
{
	towerHP -= attack;

	if (towerHP <= 0)
	{
		towerHP = 0;

		gameMode->ShowGameOverScreen();
	}

	chpWidget->ShowHealthBar(towerHP, towerMaxHP);
	gameMode->mainUIWidget->BoxHP->ShowHealthBar(towerHP, towerMaxHP);
}

