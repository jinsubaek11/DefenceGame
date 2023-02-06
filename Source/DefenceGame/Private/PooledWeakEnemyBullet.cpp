#include "PooledWeakEnemyBullet.h"


APooledWeakEnemyBullet::APooledWeakEnemyBullet()
{
	speed = 500;
	damage = 5;

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetRelativeScale3D(FVector(0.2));
	}

}


void APooledWeakEnemyBullet::OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("APooledWeakEnemyBullet::OnHitSpecificBullet"));

}