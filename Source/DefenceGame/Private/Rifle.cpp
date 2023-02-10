#include "Rifle.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"
#include <Camera/CameraComponent.h>
#include "Engine/SkeletalMeshSocket.h"
#include "Particles/ParticleSystem.h"
#include "PooledEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "GamePlayer.h"


ARifle::ARifle()
{
	PrimaryActorTick.bCanEverTick = true;
	
	weaponType = WeaponType::RIFLE;
	maxBulletCounts = 30;
	bulletCounts = maxBulletCounts;
	attackRange = 1500.f;
	att = 10;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComponent);
	
	skeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Weapons/Rifle/Mesh/SK_Rifle.SK_Rifle'"));
	if (mesh.Succeeded())
	{
		skeletalMeshComponent->SetSkeletalMesh(mesh.Object);
		skeletalMeshComponent->SetupAttachment(RootComponent);
	}

	decalComponent = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal Component"));
	ConstructorHelpers::FObjectFinder<UMaterialInterface> mat(TEXT("/Script/Engine.Material'/Game/Weapons/Generic/Materials/M_DistanceChecking.M_DistanceChecking'"));
	if (mat.Succeeded())
	{
		//decalComponent->SetDecalMaterial(mat.Object);
		originalMaterial = mat.Object;
		decalComponent->SetVisibility(false);
	}

	muzzleFlash = CreateDefaultSubobject<UParticleSystem>(TEXT("Muzzle Particle"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> muzzleParticle(TEXT("/Script/Engine.ParticleSystem'/Game/FX/Particles/Abilities/Primary/FX/P_Wraith_Primary_MuzzleFlash.P_Wraith_Primary_MuzzleFlash'"));
	if (muzzleParticle.Succeeded())
	{
		muzzleFlash = muzzleParticle.Object;
	}

	hitFlash = CreateDefaultSubobject<UParticleSystem>(TEXT("Hit Particle"));
	ConstructorHelpers::FObjectFinder<UParticleSystem> hitParticle(TEXT("/Script/Engine.ParticleSystem'/Game/FX/Particles/Abilities/Primary/FX/P_Wraith_Primary_HitCharacter.P_Wraith_Primary_HitCharacter'"));
	if (hitParticle.Succeeded())
	{
		hitFlash = hitParticle.Object;
	}

	SetActorRelativeRotation(FRotator(40, -20, 125));
	SetActorRelativeLocation(FVector(0, 0, 5));

	/*Effect Sound*/
	rifleFireSound = CreateDefaultSubobject<USoundBase>(TEXT("rifle Fire Sound"));
	ConstructorHelpers::FObjectFinder<USoundBase> rifleSound(TEXT("/Script/Engine.SoundWave'/Game/Sound/Shoot2.Shoot2'"));
	if (rifleSound.Succeeded())
	{
		rifleFireSound = (rifleSound.Object);
	}
}

void ARifle::BeginPlay()
{
	Super::BeginPlay();

	dynamicMaterial = UMaterialInstanceDynamic::Create(originalMaterial, this);
	decalComponent->SetMaterial(0, dynamicMaterial);

	decalRotation = player->GetActorRotation().Add(0, 3, 0);
}

void ARifle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	decalRotation = player->GetActorRotation().Add(0, 5, 0);

	DrawWeaponRange();
}

void ARifle::DrawWeaponRange()
{
	Super::DrawWeaponRange();

}

void ARifle::Shoot()
{
	Super::Shoot();

	if (bulletCounts <= 0)
	{
		// no bullet sound
		return;
	}

	FVector start;
	FRotator rotation;
	player->GetController()->GetPlayerViewPoint(start, rotation);
	FVector end = start + rotation.Vector() * attackRange;

	UGameplayStatics::SpawnEmitterAttached(muzzleFlash, skeletalMeshComponent, TEXT("Muzzle"));

	FHitResult hitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	bool isHit = GetWorld()->LineTraceSingleByChannel(
		hitResult, start, end, ECollisionChannel::ECC_Visibility, params
	);

	if (isHit)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), hitFlash, hitResult.Location);
		
		APooledEnemy* enemy = Cast<APooledEnemy>(hitResult.GetActor());
		if (enemy)
		{
			enemy->OnTakeDamage(att);
		}
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), rifleFireSound, GetActorLocation(), GetActorRotation());
}
