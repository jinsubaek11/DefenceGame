#include "PooledPlayerRifleBullet.h"


APooledPlayerRifleBullet::APooledPlayerRifleBullet()
{
	speed = 2000;
	damage = 10;

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetRelativeScale3D(FVector(0.25));
	}
}

void APooledPlayerRifleBullet::OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("APooledPlayerRifleBullet::OnHitSpecificBullet"));

}