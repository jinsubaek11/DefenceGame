#include "PooledObject.h"


APooledObject::APooledObject()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APooledObject::BeginPlay()
{
	Super::BeginPlay();
	
}

void APooledObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APooledObject::SetActive(bool value)
{
	isActive = value;
	SetActorHiddenInGame(!isActive);
	SetActorEnableCollision(isActive);
	SetActorTickEnabled(isActive);

	if (!isActive)
	{
		Reset();
		OnPooledObjectDespawn.Broadcast(this);
	}
}

void APooledObject::SetDeactive()
{
	SetActive(false);
	GetWorldTimerManager().ClearTimer(deactiveTimer);
}

void APooledObject::SetDeactiveTimer(float time)
{
	GetWorldTimerManager().SetTimer(deactiveTimer, this, &APooledObject::SetDeactive, time, false);
}

void APooledObject::SetIndex(int32 idx)
{
	index = idx;
}

int32 APooledObject::GetIndex() const
{
	return index;
}

bool APooledObject::IsActive() const
{
	return isActive;
}