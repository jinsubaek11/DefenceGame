#include "PooledPlayerBullet.h"
#include "Components/BoxComponent.h"
#include "PooledEnemy.h"


APooledPlayerBullet::APooledPlayerBullet()
{
	boxComponent->SetCollisionProfileName(TEXT("PlayerBulletPreset"));
}

void APooledPlayerBullet::BeginPlay()
{
	Super::BeginPlay();

	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &APooledPlayerBullet::OnHit);
	SetDeactiveTimer(3.f);
}

void APooledPlayerBullet::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("APooledPlayerBullet::OnHit"));

	//APooledEnemy* enemy = Cast<APooledEnemy>(OtherActor);

	//if (IsValid(enemy))
	//{
		OnHitSpecificBullet(OtherActor, SweepResult);
	//}
}

void APooledPlayerBullet::OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult)
{

}