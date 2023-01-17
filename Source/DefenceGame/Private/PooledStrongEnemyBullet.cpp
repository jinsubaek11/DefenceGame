#include "PooledStrongEnemyBullet.h"


APooledStrongEnemyBullet::APooledStrongEnemyBullet()
{
	speed = 500;
	damage = 15;

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetRelativeScale3D(FVector(0.2));
	}
}


void APooledStrongEnemyBullet::OnHitSpecificBullet(AActor* OtherActor)
{
	UE_LOG(LogTemp, Warning, TEXT("APooledStrongEnemyBullet::OnHitSpecificBullet"));

}