#include "Rifle.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GamePlayer.h"
#include <Camera/CameraComponent.h>
#include "Engine/SkeletalMeshSocket.h"
#include "Particles/ParticleSystem.h"
#include "PlayerRifleBulletPool.h"
#include "PooledPlayerRifleBullet.h"

ARifle::ARifle()
{
	PrimaryActorTick.bCanEverTick = true;
	
	weaponType = WeaponType::RIFLE;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComponent);
	
	meshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Weapons/Rifle/Mesh/SK_Rifle.SK_Rifle'"));
	if (mesh.Succeeded())
	{
		meshComponent->SetSkeletalMesh(mesh.Object);
		meshComponent->SetupAttachment(RootComponent);
	}

	decalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal Component"));
	//decalComponent->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UMaterialInterface> mat(TEXT("/Script/Engine.Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));
	if (mat.Succeeded())
	{
		decalComponent->SetDecalMaterial(mat.Object);
		decalComponent->SetVisibility(false);
	}

	emitParticle = CreateDefaultSubobject<UParticleSystem>(TEXT("Emit Particle"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> particle(TEXT("/Script/Engine.ParticleSystem'/Game/FX/Particles/Abilities/Primary/FX/P_Wraith_Primary_MuzzleFlash.P_Wraith_Primary_MuzzleFlash'"));
	if (particle.Succeeded())
	{
		emitParticle = particle.Object;		
	}

	SetActorRelativeRotation(FRotator(40, -20, 125));
	SetActorRelativeLocation(FVector(0, 0, 5));
}

void ARifle::BeginPlay()
{
	Super::BeginPlay();

	player = Cast<AGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	rifleBulletPool = GetWorld()->SpawnActor<APlayerRifleBulletPool>();
}

void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawRifleRange();
}

void ARifle::DrawRifleRange()
{
	if (!player) return;

	FVector start;
	FRotator rotation;
	player->GetController()->GetPlayerViewPoint(start, rotation);
	FVector end = start +  rotation.Vector() * attackRange;

	FVector start2 = player->GetActorLocation();
	FVector end2 = start2 + rotation.Vector() * attackRange;

	FHitResult hitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	bool isHit = GetWorld()->LineTraceSingleByChannel(
		hitResult, start2, end, ECollisionChannel::ECC_Visibility, params
	);

	FVector decalSize;

	if (isHit)
	{
		//float length = (hitResult.Location - player->GetActorLocation()).Length();
		decalSize = hitResult.Location - player->GetActorLocation();
		decalSize.Y = 20;
		decalSize.Z = 10;
		DrawDebugLine(GetWorld(), start, end, FColor::Red);
	}

	//UE_LOG(LogTemp, Warning, TEXT("%f"), hitResult.Distance);
	//UE_LOG(LogTemp, Warning, TEXT("%d"), hitResult.bBlockingHit);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *hitResult.ImpactPoint.ToString());
	

	//FVector decalLocation = player->GetActorLocation() + player->GetActorForwardVector() * decalSize.X;
	FVector decalLocation = player->GetActorLocation() + player->GetActorForwardVector() * 600;
	decalLocation += player->GetActorRightVector() * 50;
	decalLocation.Z = 0;
	FRotator decalRotation = player->GetActorRotation().Add(0, 5, 0);
	//decalComponent->DecalSize = decalSize;
	decalComponent->DecalSize = FVector(600, 20, 10);
	decalComponent->SetWorldLocation(decalLocation);
	decalComponent->SetWorldRotation(decalRotation);
	//decalComponent->SetRotation
	//decalComponent->SetWorldRotation(FRotator(0, player->GetControlRotation().Yaw, 0));
	decalComponent->SetVisibility(true);
}

void ARifle::Shoot()
{
	if (!player) return;

	FVector start;
	FRotator rotation;
	player->GetController()->GetPlayerViewPoint(start, rotation);
	FVector end = start + rotation.Vector() * attackRange;

	//FTransform muzzleTransform = meshComponent->GetSocketTransform(TEXT("Muzzle"));
	//UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), emitParticle, muzzleTransform, true);

	UGameplayStatics::SpawnEmitterAttached(emitParticle, meshComponent, TEXT("Muzzle"));
	UE_LOG(LogTemp, Warning, TEXT("Shoot"));


	FVector spawnPosition = meshComponent->GetSocketLocation(TEXT("Muzzle"));
	APooledPlayerRifleBullet* bullet = Cast<APooledPlayerRifleBullet>(rifleBulletPool->SpawnPooledObject(spawnPosition, rotation));
	bullet->SetDeactiveTimer(2);


	//FHitResult hitResult;
	//FCollisionQueryParams params;
	//params.AddIgnoredActor(player);

	//bool isHit = GetWorld()->LineTraceSingleByChannel(
	//	hitResult, start, end, ECollisionChannel::ECC_Visibility, params
	//);

	//if (isHit)
	//{
	//	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), )

	//	DrawDebugLine(GetWorld(), start, end, FColor::Red);
	//}
}