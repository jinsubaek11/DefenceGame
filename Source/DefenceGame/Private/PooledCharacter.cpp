#include "PooledCharacter.h"
#include "Components/CapsuleComponent.h"


APooledCharacter::APooledCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APooledCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APooledCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APooledCharacter::SetActive(bool value)
{
	isActive = value;
	SetActorHiddenInGame(!isActive);
	SetActorEnableCollision(isActive);
	SetActorTickEnabled(isActive);

	if (!isActive)
	{
		Reset();
		OnPooledCharacterDespawn.Broadcast(this);
	}
}

void APooledCharacter::SetIndex(int32 idx)
{
	index = idx;
}

int32 APooledCharacter::GetIndex() const
{
	return index;
}

bool APooledCharacter::IsActive() const
{
	return isActive;
}




