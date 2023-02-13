#include "PooledPlayerTurretBullet.h"
#include "Components/BoxComponent.h"
#include "PooledEnemy.h"


APooledPlayerTurretBullet::APooledPlayerTurretBullet()
{
	speed = 1000;
	damage = 10;

	boxComponent->SetBoxExtent(FVector(20, 5, 5));

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Game/Item/Turret/Meshes/SM_Projectile.SM_Projectile'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetRelativeScale3D(FVector(1, 0.7, 0.7));
	}
}

void APooledPlayerTurretBullet::OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("APooledPlayerTurretBullet::OnHitSpecificBullet"));

	APooledEnemy* enemy = Cast<APooledEnemy>(OtherActor);

	if (IsValid(enemy))
	{
		enemy->OnTakeDamage(GetDamage());
		SetActive(false);
	}

}