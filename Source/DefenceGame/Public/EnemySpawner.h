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
	void Upgrade();
	void ResetSpawn();

public:
	UPROPERTY(EditAnywhere)
	class UBoxComponent* boxComponent;
	UPROPERTY(EditAnywhere)
	class UArrowComponent* arrowComponent;
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* meshComponent;

private:
	UPROPERTY()
	class AStrongEnemyPool* strongEnemyPool;
	UPROPERTY()
	class ANormalEnemyPool* normalEnemyPool;
	UPROPERTY()
	class AWeakEnemyPool* weakEnemyPool;

	float strongEnemySpawnTime;
	float normalEnemySpawnTime;
	float weakEnemySpawnTime;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess="true"))
	float strongEnemyCoolTime = 31.3f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float normalEnemyCoolTime = 23.1f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float weakEnemyCoolTime = 15.3f;
};
