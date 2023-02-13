#include "CharacterPool.h"
#include "PooledCharacter.h"


ACharacterPool::ACharacterPool()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACharacterPool::BeginPlay()
{
	Super::BeginPlay();

	spawnLocation = FVector(0, 0, -1000);
	UWorld* world = GetWorld();

	if (world)
	{
		for (uint16 i = 0; i < poolSize; ++i)
		{
			APooledCharacter* character = world->SpawnActor<APooledCharacter>(
				classType, spawnLocation, FRotator().ZeroRotator
			);

			if (character)
			{
				character->SetActive(false);
				character->SetIndex(i);
				character->OnPooledCharacterDespawn.AddDynamic(
					this, &ACharacterPool::OnPooledCharacterDespawn
				);
				characterPool.Emplace(character);
			}
		}
	}
}

APooledCharacter* ACharacterPool::SpawnPooledCharacter(FVector spawnPosition)
{
	for (APooledCharacter* character : characterPool)
	{
		if (character && !character->IsActive())
		{
			character->SetActorLocation(spawnPosition);
			character->SetActive(true);
			spawnedPoolIndexes.Emplace(character->GetIndex());
			return character;
		}
	}

	//UE_LOG(LogTemp, Warning, TEXT("%s MAX"), *classType->GetName());

	//if (characterPool.Num() > 0 && spawnedPoolIndexes.Num() > 0)
	//{
	//	uint16 targetIndex = spawnedPoolIndexes[0];

	//	spawnedPoolIndexes.Remove(targetIndex);
	//	APooledCharacter* character = characterPool[targetIndex];

	//	if (character)
	//	{
	//		character->SetActive(false);
	//		character->SetActorLocation(spawnPosition);
	//		character->SetActive(true);

	//		characterPool.Emplace(character);

	//		return character;
	//	}
	//}

	return nullptr;
}

void ACharacterPool::OnPooledCharacterDespawn(APooledCharacter* pooledCharacter)
{
	spawnedPoolIndexes.Remove(pooledCharacter->GetIndex());
	pooledCharacter->SetActorLocation(spawnLocation);

	UE_LOG(LogTemp, Warning, TEXT("OnPooledCharacterDespawn"));
}

TArray<class APooledCharacter*> ACharacterPool::GetPool() const
{
	return characterPool;
}

int32 ACharacterPool::GetPoolSize()
{
	return characterPool.Num();
}

void ACharacterPool::SetAllDeactivate()
{
	for (APooledCharacter* character : characterPool)
	{
		if (!character) return;

		character->SetActive(false);
		character->ResetState();
	}
}
