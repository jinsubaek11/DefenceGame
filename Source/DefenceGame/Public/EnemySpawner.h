#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class DEFENCEGAME_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySpawner();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;

private:
	class AStrongEnemyPool* strongEnemyPool;
	class ANormalEnemyPool* normalEnemyPool;
	class AWeakEnemyPool* weakEnemyPool;

	float strongEnemySpawnTime;
	float normalEnemySpawnTime;
	float weakEnemySpawnTime;

	float strongEnemyCoolTime = 1.5f;
	float normalEnemyCoolTime = 0.8f;
	float weakEnemyCoolTime = 0.5f;
};
