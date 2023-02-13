#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BossSpawner.generated.h"

UCLASS()
class DEFENCEGAME_API ABossSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ABossSpawner();

protected:
	virtual void BeginPlay() override;

public:
	void SpawnBoss();
	void ResetSpawn();
	void Upgrade();

private:
	class USceneComponent* sceneComponent;
	class ABossEnemyPool* bossEnemyPool;
};
