#include "PooledPlayerBazookaBullet.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "PooledEnemy.h"


APooledPlayerBazookaBullet::APooledPlayerBazookaBullet()
{
	speed = 3500;
	damage = 50;

	boxComponent->SetBoxExtent(FVector(10, 60, 10));

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Game/Weapons/Bazooka/Mesh/Missile.Missile'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetRelativeLocationAndRotation(FVector(0, 70, 0), FRotator(-90, 0, 0));
		meshComponent->SetRelativeScale3D(FVector(0.1, 0.1, 0.2));
	}

	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (particle.Succeeded())
	{
		explosion = particle.Object;
		//explosion->
	}

	/*Effect Sound*/
	bazookaFireSound = CreateDefaultSubobject<USoundBase>(TEXT("bazookaFireSound"));
	ConstructorHelpers::FObjectFinder<USoundBase> bazookaSound(TEXT("/Script/Engine.SoundWave'/Game/Sound/Rocekt1.Rocekt1'"));
	if (bazookaSound.Succeeded())
	{
		bazookaFireSound = (bazookaSound.Object);
	}
}

void APooledPlayerBazookaBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (autoDestroyRange)
	{
		currentPosition = GetActorLocation();
		
		if ((currentPosition - spawnPosition).Length() >= autoDestroyRange)
		{
			SpawnExplosionParticle(currentPosition);
			SetActive(false);
		}
	}
}

void APooledPlayerBazookaBullet::SetDestroyRange(FVector startPosition, float range)
{
	spawnPosition = startPosition;
	autoDestroyRange = range;
}

void APooledPlayerBazookaBullet::SpawnExplosionParticle(const FVector& location)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion, location);
}

void APooledPlayerBazookaBullet::OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("APooledPlayerBazookaBullet::OnHitSpecificBullet"));
	
	SpawnExplosionParticle(GetActorLocation());

	TArray<FHitResult> hitResults;
	FVector sweepStart = GetActorLocation();
	FVector sweepEnd = GetActorLocation();
	FCollisionShape sphereCollision = FCollisionShape::MakeSphere(150.f);
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), sphereCollision.GetSphereRadius(), 50, FColor::Green, false, 3.f);

	bool isHit = GetWorld()->SweepMultiByObjectType(hitResults, sweepStart, sweepEnd, FQuat::Identity, objectQueryParams, sphereCollision);
	
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), bazookaFireSound, GetActorLocation(), GetActorRotation());

	if (isHit)
	{
		for (auto hitResult : hitResults)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s"), *hitResult.GetActor()->GetName());
			APooledEnemy* enemy =  Cast<APooledEnemy>(hitResult.GetActor());
			if (enemy)
			{
				enemy->OnTakeDamage(GetDamage());
			}
		}
	}

	SetActive(false);
}