#include "PooledNormalEnemyBullet.h"


APooledNormalEnemyBullet::APooledNormalEnemyBullet()
{
	speed = 500;
	damage = 10;

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetRelativeScale3D(FVector(0.25));
	}
}

void APooledNormalEnemyBullet::OnHitSpecificBullet(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("APooledNormalEnemyBullet::OnHitSpecificBullet"));

}