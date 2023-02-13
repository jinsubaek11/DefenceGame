#include "PooledPlayerTurretBullet.h"
#include "Components/BoxComponent.h"
#include "PooledEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"


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

	turretparticle = CreateDefaultSubobject<UParticleSystem>(TEXT("turretparticle"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> turretparticles(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Hit/P_Brick.P_Brick'"));
	if (turretparticles.Succeeded())
	{
		turretparticle = turretparticles.Object;		
	}

}

void APooledPlayerTurretBullet::OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("APooledPlayerTurretBullet::OnHitSpecificBullet"));

	APooledEnemy* enemy = Cast<APooledEnemy>(OtherActor);

	if (IsValid(enemy))
	{
		enemy->OnTakeDamage(GetDamage());
		/*Attatch Particles 일단 빌드만 시키게 임시로 이상한데다 붙임*/
		//UGameplayStatics::SpawnEmitterAttached(turretFlash, towerTurretComponent);
		SetActive(false);
	}

}