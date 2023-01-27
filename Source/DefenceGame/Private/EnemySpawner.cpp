#include "EnemySpawner.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "StrongEnemyPool.h"
#include "NormalEnemyPool.h"
#include "WeakEnemyPool.h"
#include "PooledEnemy.h"
#include "EnemyAIController.h"


AEnemySpawner::AEnemySpawner()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComponent);

	arrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));
	arrowComponent->SetupAttachment(RootComponent);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	meshComponent->SetupAttachment(RootComponent);
}

void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* world = GetWorld();

	strongEnemyPool = world->SpawnActor<AStrongEnemyPool>();
	normalEnemyPool = world->SpawnActor<ANormalEnemyPool>();
	weakEnemyPool = world->SpawnActor<AWeakEnemyPool>();
}

void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	strongEnemySpawnTime += DeltaTime;
	normalEnemySpawnTime += DeltaTime;
	weakEnemySpawnTime += DeltaTime;

	if (strongEnemySpawnTime >= strongEnemyCoolTime)
	{
		strongEnemyPool->SpawnPooledCharacter(GetActorLocation());
		strongEnemySpawnTime = 0;
		UE_LOG(LogTemp, Warning, TEXT("strong enemy spawned"));
	}

	if (normalEnemySpawnTime >= normalEnemyCoolTime)
	{
		normalEnemyPool->SpawnPooledCharacter(GetActorLocation());
		normalEnemySpawnTime = 0;
		UE_LOG(LogTemp, Warning, TEXT("normal enemy spawned"));
	}

	if (weakEnemySpawnTime >= weakEnemyCoolTime)
	{
		weakEnemyPool->SpawnPooledCharacter(GetActorLocation());
		weakEnemySpawnTime = 0;
		UE_LOG(LogTemp, Warning, TEXT("weak enemy spawned"));
	}
}

