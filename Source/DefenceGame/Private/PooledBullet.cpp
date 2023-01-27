#include "PooledBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


APooledBullet::APooledBullet()
{
	boxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	SetRootComponent(boxComponent);

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	meshComponent->SetupAttachment(RootComponent);
}

void APooledBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * DeltaTime);
}

int32 APooledBullet::GetDamage() const
{
	return damage;
}