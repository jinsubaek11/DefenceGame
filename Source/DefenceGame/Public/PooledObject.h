#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PooledObject.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledObjectDespawn, APooledObject*, pooledObject);

UCLASS()
class DEFENCEGAME_API APooledObject : public AActor
{
	GENERATED_BODY()
	
public:	
	APooledObject();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	void SetActive(bool value);
	void SetDeactive();
	void SetDeactiveTimer(float time);
	void SetIndex(int32 index);
	int32 GetIndex() const;
	bool IsActive() const;

	FOnPooledObjectDespawn OnPooledObjectDespawn;

private:
	int32 index;
	bool isActive;

	FTimerHandle deactiveTimer;
};
