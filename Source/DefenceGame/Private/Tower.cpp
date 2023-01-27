#include "Tower.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "HPWidget.h"

ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	boxComponent->SetBoxExtent(FVector(40, 40, 100));
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

	ConstructorHelpers::FClassFinder<UUserWidget> hpwidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/BP_HPWidget'"));

	if (hpwidget.Succeeded())
	{
		towerHPui->SetWidgetClass(hpwidget.Class);
		towerHPui->SetDrawSize(FVector2D(500, 30));
		chpWidget = Cast<UHPWidget>(towerHPui->GetWidget());
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	if(chpWidget)
	{
		chpWidget->GetTowerHP(1);
		chpWidget->ShowHealthBar(1);
	}
	UE_LOG(LogTemp, Warning, TEXT("Show Health Number"))
	
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
