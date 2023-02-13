#include "EnemySpawner.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "StrongEnemyPool.h"
#include "NormalEnemyPool.h"
#include "WeakEnemyPool.h"
#include "PooledEnemy.h"
#include "EnemyAIController.h"
#include "PooledEnemy.h"


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
		strongEnemyPool->SpawnPooledCharacter(GetActorLocation() + GetActorForwardVector() * 100);
		strongEnemySpawnTime = 0;
		//UE_LOG(LogTemp, Warning, TEXT("strong enemy spawned"));
	}

	if (normalEnemySpawnTime >= normalEnemyCoolTime)
	{
		normalEnemyPool->SpawnPooledCharacter(GetActorLocation() + GetActorForwardVector() * 100);
		normalEnemySpawnTime = 0;
		//UE_LOG(LogTemp, Warning, TEXT("normal enemy spawned"));
	}

	if (weakEnemySpawnTime >= weakEnemyCoolTime)
	{
		weakEnemyPool->SpawnPooledCharacter(GetActorLocation() + GetActorForwardVector() * 100);
		weakEnemySpawnTime = 0;
		//UE_LOG(LogTemp, Warning, TEXT("weak enemy spawned"));
	}
}

void AEnemySpawner::ResetSpawn()
{
	strongEnemyPool->SetAllDeactivate();
	normalEnemyPool->SetAllDeactivate();
	weakEnemyPool->SetAllDeactivate();

	strongEnemySpawnTime = 0;
	normalEnemySpawnTime = 0;
	weakEnemySpawnTime = 0;
}

void AEnemySpawner::Upgrade()
{
	for (APooledCharacter* pooledCharacter : strongEnemyPool->GetPool())
	{
		APooledEnemy* enemy = Cast<APooledEnemy>(pooledCharacter);
		if (!enemy) return;

		enemy->Upgrade();
	}

	for (APooledCharacter* pooledCharacter : normalEnemyPool->GetPool())
	{
		APooledEnemy* enemy = Cast<APooledEnemy>(pooledCharacter);
		if (!enemy) return;

		enemy->Upgrade();
	}

	for (APooledCharacter* pooledCharacter : weakEnemyPool->GetPool())
	{
		APooledEnemy* enemy = Cast<APooledEnemy>(pooledCharacter);
		if (!enemy) return;

		enemy->Upgrade();
	}
}
