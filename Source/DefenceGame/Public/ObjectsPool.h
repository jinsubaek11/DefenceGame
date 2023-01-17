#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectsPool.generated.h"



UCLASS()
class DEFENCEGAME_API AObjectsPool : public AActor
{
	GENERATED_BODY()
	
public:	
	AObjectsPool();

protected:
	virtual void BeginPlay() override;

public:
	class APooledObject* SpawnPooledObject(FVector spawnPosition, FRotator spawnRotator = FRotator::ZeroRotator);
	int32 GetPoolSize();
	int32 GetActiveObjectCount();

private:
	UFUNCTION()
	void OnPooledObjectDespawn(class APooledObject* pooledObject);

protected:
	UClass* classType;
	int32 poolSize;

private:
	TArray<class APooledObject*> objectPool;
	TArray<int32> spawnedPoolIndexes;
};
