#include "PooledBossEnemyBullet.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "PooledBossEnemy.h"
#include "Sword.h"
#include "Bow.h"
#include "GamePlayer.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"


APooledBossEnemyBullet::APooledBossEnemyBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	speed = 1500;
	damage = 30;

	boxComponent->SetBoxExtent(FVector(80, 3, 3));

	ConstructorHelpers::FObjectFinder<UStaticMesh> mesh(TEXT("/Script/Engine.StaticMesh'/Game/Weapons/Bow/Mesh/Arrow.Arrow'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetStaticMesh(mesh.Object);
		meshComponent->SetRelativeLocation(FVector(90, 0, 0));
		meshComponent->SetRelativeRotation(FRotator(90, 0, 0));
		meshComponent->SetRelativeScale3D(FVector(3, 6, 2));
		meshComponent->bReceivesDecals = false;
	}

	decalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal Component"));

	ConstructorHelpers::FObjectFinder<UMaterialInterface> decal(TEXT("/Script/Engine.Material'/Game/Material/M_Explode.M_Explode'"));
	if (decal.Succeeded())
	{
		decalComponent->SetDecalMaterial(decal.Object);
		decalComponent->SetRelativeRotation(FRotator(-90, 90, 0));
		decalComponent->SetRelativeScale3D(FVector(1.5));
		decalComponent->DecalSize = FVector(36, 240, 240);
		decalComponent->SetVisibility(false);
	}

	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(TEXT("/Script/Engine.ParticleSystem'/Game/StarterContent/Particles/P_Explosion.P_Explosion'"));
	if (particle.Succeeded())
	{
		explosion = particle.Object;
	}
}

void APooledBossEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (autoDestroyRange)
	{
		currentPosition = GetActorLocation();

		if ((currentPosition - spawnPosition).Length() >= autoDestroyRange)
		{
			SpawnEffect(currentPosition);
			Explode();
			SetActive(false);
		}
	}
}

void APooledBossEnemyBullet::SetDestroyRange(FVector startPosition, float range)
{
	spawnPosition = startPosition;
	autoDestroyRange = range;
}

void APooledBossEnemyBullet::SpawnEffect(FVector location)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), explosion, location);
}

void APooledBossEnemyBullet::OnHitSpecificBullet(AActor* OtherActor, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("APooledBossEnemyBullet::OnHitSpecificBullet"));

	Explode();
}

void APooledBossEnemyBullet::DrawExplosionRange()
{
	FHitResult hitResult;
	FCollisionQueryParams params;
	FVector start = spawnPosition;
	FVector end = spawnPosition + GetActorForwardVector() * autoDestroyRange;
	FVector explosionLocation = end;
	
	APooledBossEnemy* boss = Cast<APooledBossEnemy>(UGameplayStatics::GetActorOfClass(GetWorld(), APooledBossEnemy::StaticClass()));
	if (boss)
	{
		params.AddIgnoredActor(boss);
		params.AddIgnoredActor(boss->sword);
		params.AddIgnoredActor(boss->bow);
	}
	
	bool isHit = GetWorld()->LineTraceSingleByChannel(
		hitResult, start, end, ECollisionChannel::ECC_Visibility, params
	);

	if (isHit)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *hitResult.GetActor()->GetName());
		explosionLocation = hitResult.Location;
	}

	FVector decalLocation = explosionLocation - GetActorForwardVector() * 180;
	explosionLocation.Z = 0;
	decalComponent->SetRelativeLocation(explosionLocation);
	decalComponent->SetVisibility(true);
}

void APooledBossEnemyBullet::Explode()
{
	TArray<FHitResult> hitResults;
	FVector sweepStart = GetActorLocation();
	FVector sweepEnd = GetActorLocation();
	FCollisionShape sphereCollision = FCollisionShape::MakeSphere(350.f);
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel1);
	objectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel5);
	objectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel7);
	objectQueryParams.RemoveObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), sphereCollision.GetSphereRadius(), 50, FColor::Green, false, 3.f);

	bool isHit = GetWorld()->SweepMultiByObjectType(hitResults, sweepStart, sweepEnd, FQuat::Identity, objectQueryParams, sphereCollision);

	if (isHit)
	{
		for (auto hitResult : hitResults)
		{
			AGamePlayer* player = Cast<AGamePlayer>(hitResult.GetActor());

			if (player)
			{
				player->OnTakeDamage(GetDamage());
			}

			ATower* tower = Cast<ATower>(hitResult.GetActor());

			if (tower)
			{
				tower->OnTakeDamage(GetDamage());
			}
		}
	}
}
