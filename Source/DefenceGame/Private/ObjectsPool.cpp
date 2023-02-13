#include "ObjectsPool.h"
#include "PooledObject.h"


AObjectsPool::AObjectsPool()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AObjectsPool::BeginPlay()
{
	Super::BeginPlay();
	
	UWorld* world = GetWorld();

	if (world)
	{
		for (int i = 0; i < poolSize; i++)
		{
			APooledObject* object = world->SpawnActor<APooledObject>(
				classType, FVector(0, 0, 1000), FRotator::ZeroRotator
			);

			if (object)
			{
				object->SetActive(false);
				object->SetIndex(i);
				object->OnPooledObjectDespawn.AddDynamic(
					this, &AObjectsPool::OnPooledObjectDespawn
				);
				objectPool.Emplace(object);
			}
		}
	}
}

APooledObject* AObjectsPool::SpawnPooledObject(FVector spawnPosition, FRotator spawnRotator)
{
	//if (!objectPool) return nullptr;

	for (APooledObject* object : objectPool)
	{
		if (object && !object->IsActive())
		{
			object->SetActorLocationAndRotation(spawnPosition, spawnRotator);
			object->SetActive(true);
			spawnedPoolIndexes.Emplace(object->GetIndex());
			return object;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("%s MAX"), *classType->GetName());

	return nullptr;
}


int32 AObjectsPool::GetPoolSize()
{
	return objectPool.Num();
}

int32 AObjectsPool::GetActiveObjectCount()
{
	return spawnedPoolIndexes.Num();
}

void AObjectsPool::OnPooledObjectDespawn(APooledObject* pooledObject)
{
	spawnedPoolIndexes.Remove(pooledObject->GetIndex());
	pooledObject->SetActorLocation(GetActorLocation());
}



