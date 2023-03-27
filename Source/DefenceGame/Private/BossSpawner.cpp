#include "BossSpawner.h"
#include "Components/SceneComponent.h"
#include "BossEnemyPool.h"
#include "PooledEnemy.h"


ABossSpawner::ABossSpawner()
{
	sceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	SetRootComponent(sceneComponent);
}

void ABossSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	bossEnemyPool = GetWorld()->SpawnActor<ABossEnemyPool>();
}

void ABossSpawner::SpawnBoss()
{
	bossEnemyPool->SpawnPooledCharacter(GetActorLocation() + GetActorForwardVector() * 500);
}

void ABossSpawner::ResetSpawn()
{
	bossEnemyPool->SetAllDeactivate();
}

void ABossSpawner::Upgrade()
{
	for (APooledCharacter* pooledCharacter : bossEnemyPool->GetPool())
	{
		APooledEnemy* enemy = Cast<APooledEnemy>(pooledCharacter);
		if (!enemy) return;

		enemy->Upgrade();
	}
}


