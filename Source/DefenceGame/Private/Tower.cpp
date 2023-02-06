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


ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	boxComponent->SetBoxExtent(FVector(40, 40, 100));
	boxComponent->SetCollisionProfileName(TEXT("TowerPreset"));
	SetRootComponent(boxComponent);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Game/Asian_Village/meshes/building/SM_tower_02.SM_tower_02'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetRelativeScale3D(FVector(0.1));
		meshComponent->SetRelativeLocation(FVector(0, 0, -110));
		meshComponent->SetupAttachment(RootComponent);
	}

	towerHPui = CreateDefaultSubobject<UWidgetComponent>(TEXT("towerHPui"));
	towerHPui->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	towerHPui->SetRelativeRotation(FRotator(0, -180, 0));
	towerHPui->SetWidgetSpace(EWidgetSpace::Screen);
	//towerHPui->SetWidgetClass(widgetFactory);

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

	chpWidget = Cast<UHPWidget>(towerHPui->GetWidget());

	if(chpWidget)
	{
		chpWidget->SetTowerHP(chpWidget->towerMaxHP);
		//UE_LOG(LogTemp,Warning, TEXT("beginPlay %f"), chpWidget->towerMaxHP)
	}

	

}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto cm = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	//cm->GetCameraLocation();

	//gPlayer = Cast<AGamePlayer>();

	//float dist = gPlayer->GetDistance(cm->GetCameraLocation());

	
	FRotator newRotation = UKismetMathLibrary::MakeRotFromXZ(
	cm->GetCameraLocation() - GetActorLocation(),
	GetActorUpVector());

	towerHPui->SetWorldRotation(newRotation);
}

void ATower::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Enemy Axe와 충돌하면
	//AEnemyAxe* eaxe = Cast<AEnemyAxe>(OtherActor);
	//if(!eaxe) return;
	//체력이 떨어진다 tower의 hp - axe의attack score

	//AFatalTeeth* fteeth = Cast<AFatalTeeth>(OtherActor);
	//if (!fteeth) return;
	//체력이 떨어진다 tower의 hp - teeth의attack score
	
}

void ATower::OnTakeTowerDamage(float attack)
{
	towerHP -= attack;
	UE_LOG(LogTemp, Warning, TEXT("ATower::OnTakeTowerDamage %f"), towerHP)

	chpWidget->SetTowerHP(towerHP);
}

