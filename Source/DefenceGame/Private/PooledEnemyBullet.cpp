#include "PooledEnemyBullet.h"
#include "Components/BoxComponent.h"
#include "GamePlayer.h"
#include "Item.h"
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
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("APooledEnemyBullet::OnHit"));

	AGamePlayer* player = Cast<AGamePlayer>(OtherActor);
	if (IsValid(player))
	{
		//OnHitSpecificBullet(player, SweepResult);
		player->OnTakeDamage(GetDamage());
		SetActive(false);
	}

	AItem* item = Cast<AItem>(OtherActor);
	if (IsValid(item))
	{
		item->OnTakeDamage(GetDamage());
		SetActive(false);
	}

	UHPWidget* hpwidget = Cast<UHPWidget>(OtherActor);
	if (hpwidget != nullptr)
	{
		//Bullet�� ������ Tower�� hp�� �پ���
		hpwidget->GetTowerHP(attackScore);
	}
	
}

void APooledEnemyBullet::OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult)
{

}

