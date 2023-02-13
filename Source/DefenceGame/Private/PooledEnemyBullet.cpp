#include "PooledEnemyBullet.h"
#include "Components/BoxComponent.h"
#include "GamePlayer.h"
#include "Item.h"
#include "Tower.h"
#include "HPWidget.h"


APooledEnemyBullet::APooledEnemyBullet()
{
	boxComponent->SetCollisionProfileName(TEXT("EnemyBulletPreset"));
}

void APooledEnemyBullet::BeginPlay()
{
	Super::BeginPlay();

	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &APooledEnemyBullet::OnHit);
	SetDeactiveTimer(3.f);
}

void APooledEnemyBullet::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SpawnEffect(GetActorLocation());

	AGamePlayer* player = Cast<AGamePlayer>(OtherActor);
	if (IsValid(player))
	{
		player->OnTakeDamage(GetDamage());
		OnHitSpecificBullet(player, SweepResult);

		SetActive(false);
	}

	AItem* item = Cast<AItem>(OtherActor);
	if (IsValid(item))
	{
		item->OnTakeDamage(GetDamage());
		OnHitSpecificBullet(item, SweepResult);
		SetActive(false);
	}

	ATower* tower = Cast<ATower>(OtherActor);
	if (IsValid(tower))
	{
		tower->OnTakeDamage(GetDamage());
		OnHitSpecificBullet(tower, SweepResult);

		SetActive(false);
	}
}

void APooledEnemyBullet::SpawnEffect(FVector location)
{

}


void APooledEnemyBullet::OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult)
{

}

