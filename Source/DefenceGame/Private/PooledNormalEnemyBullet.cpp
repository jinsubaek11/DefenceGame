#include "PooledNormalEnemyBullet.h"

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

APooledNormalEnemyBullet::APooledNormalEnemyBullet()
{
	speed = 500;
	damage = 10;

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetRelativeLocationAndRotation(FVector(0, 50, 64), FRotator(-90, 0, 0));
		meshComponent->SetRelativeScale3D(FVector(0.25));
	}

	/*ConstructorHelpers::FObjectFinder<UParticleSystem> particle(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (particle.Succeeded())
	{
		UGameplayStatics::SpawnEmitterAttached(TEXT("exp"))
		eExplosion = particle.Object;
	}*/
}

void APooledNormalEnemyBullet::OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("APooledNormalEnemyBullet::OnHitSpecificBullet"));

}