#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterPool.generated.h"

UCLASS()
class DEFENCEGAME_API ACharacterPool : public AActor
{
	GENERATED_BODY()
	
public:	
	ACharacterPool();

protected:
	virtual void BeginPlay() override;

public:
	void SetAllDeactivate();
	class APooledCharacter* SpawnPooledCharacter(FVector spawnPosition);
	TArray<class APooledCharacter*> GetPool() const;
	int32 GetPoolSize();

private:
	UFUNCTION()
	void OnPooledCharacterDespawn(class APooledCharacter* pooledCharacter);

protected:
	class UClass* classType;
	int32 poolSize = 10;

private:
	TArray<class APooledCharacter*> characterPool;
	TArray<int32> spawnedPoolIndexes;

	FVector spawnLocation;
};
