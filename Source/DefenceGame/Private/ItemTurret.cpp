#include "ItemTurret.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PooledPlayerTurretBullet.h"
#include "PlayerTurretBulletPool.h"
#include "PooledEnemy.h"


AItemTurret::AItemTurret()
{
	PrimaryActorTick.bCanEverTick = true;

	type = ItemType::TURRET;
	hp = 50.f;
	maxHp = hp;
	coolTime = 10.f;

	boxComponent->SetBoxExtent(FVector(30, 30, 55));
	boxComponent->SetCollisionProfileName(TEXT("ItemPreset"));

	towerTurretComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower Turret Mesh"));
	towerTurretComponent->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> towerTurretMesh(TEXT("/Script/Engine.StaticMesh'/Game/Item/Turret/Meshes/SM_TowerTurret.SM_TowerTurret'"));
	if (towerTurretMesh.Succeeded())
	{
		towerTurretComponent->SetStaticMesh(towerTurretMesh.Object);
		towerTurretComponent->SetRelativeLocation(FVector(0, 0, -50));
		towerTurretComponent->SetRelativeRotation(FRotator(0, 0, 0));
	}

	towerBaseComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tower Base Mesh"));
	towerBaseComponent->SetupAttachment(RootComponent);
	ConstructorHelpers::FObjectFinder<UStaticMesh> towerBaseMesh(TEXT("/Script/Engine.StaticMesh'/Game/Item/Turret/Meshes/SM_TowerBase.SM_TowerBase'"));
	if (towerBaseMesh.Succeeded())
	{
		towerBaseComponent->SetStaticMesh(towerBaseMesh.Object);
		towerBaseComponent->SetRelativeLocation(FVector(0, 0, -50));
		towerBaseComponent->SetRelativeRotation(FRotator(0, 0, 0));
	}

	ConstructorHelpers::FObjectFinder<UMaterialInterface> mat(TEXT("/Script/Engine.Material'/Game/Material/M_ObstacleGreen.M_ObstacleGreen'"));
	if (mat.Succeeded())
	{
		originalTowerTurretMaterial = towerTurretComponent->GetMaterials();
		originalTowerBaseMaterial = towerBaseComponent->GetMaterials();
		transparentMaterial = mat.Object;
	}

	

	/*Effect Sound*/
	turretFireSound = CreateDefaultSubobject<USoundBase>(TEXT("turret Fire Sound"));
	ConstructorHelpers::FObjectFinder<USoundBase> turretSound(TEXT("/Script/Engine.SoundWave'/Game/Sound/Shoot4.Shoot4'"));
	if (turretSound.Succeeded())
	{
		turretFireSound = (turretSound.Object);
	}

	turretinstallSound = CreateDefaultSubobject<USoundBase>(TEXT("turret install Sound"));
	ConstructorHelpers::FObjectFinder<USoundBase> turretinstalledSound(TEXT("/Script/Engine.SoundWave'/Game/Sound/InstallTurret.InstallTurret'"));
	if (turretinstalledSound.Succeeded())
	{
		turretinstallSound = (turretinstalledSound.Object);
	}
}

void AItemTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isSetSucceed) return;

	currentTime += DeltaTime;

	TArray<FHitResult> hitResults;
	FVector sweepStart = GetActorLocation();
	FVector sweepEnd = GetActorLocation();
	FCollisionShape sphereCollision = FCollisionShape::MakeSphere(600.f);
	FCollisionObjectQueryParams objectQueryParams;
	objectQueryParams.AddObjectTypesToQuery(ECollisionChannel::ECC_GameTraceChannel2);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), sphereCollision.GetSphereRadius(), 50, FColor::Green, false);

	bool isHit = GetWorld()->SweepMultiByObjectType(hitResults, sweepStart, sweepEnd, FQuat::Identity, objectQueryParams, sphereCollision);

	APooledEnemy* targetEnemy = nullptr;
	float distance = 123456789;

	if (isHit)
	{
		for (auto hitResult : hitResults)
		{
			AActor* hitActor = hitResult.GetActor();

			if (!hitActor) return;

			if (distance > GetDistanceTo(hitActor))
			{
				targetEnemy = Cast<APooledEnemy>(hitActor);
				distance = GetDistanceTo(targetEnemy);
			 }
		}
	}

	if (targetEnemy && currentTime >= shootCoolTime)
	{
		Shoot(targetEnemy);
		currentTime = 0;
	}
}

void AItemTurret::BeginPlay()
{
	Super::BeginPlay();

	turretBulletPool = GetWorld()->SpawnActor<APlayerTurretBulletPool>();

	dynamicMaterial = UMaterialInstanceDynamic::Create(transparentMaterial, this);
	for (int i = 0; i < towerTurretComponent->GetMaterials().Num(); i++)
	{
		towerTurretComponent->SetMaterial(i, dynamicMaterial);
	}

	for (int i = 0; i < towerBaseComponent->GetMaterials().Num(); i++)
	{
		towerBaseComponent->SetMaterial(i, dynamicMaterial);
	}
}

void AItemTurret::StareEnemy(FRotator enemyRotation)
{
	FRotator rotation = FMath::RInterpTo(
		towerTurretComponent->GetComponentRotation(), enemyRotation,
		UGameplayStatics::GetWorldDeltaSeconds(this), 50.f
	);

	towerTurretComponent->SetWorldRotation(rotation);
}

void AItemTurret::Shoot(APooledEnemy* target)
{
	FVector direction = target->GetActorLocation() - GetActorLocation();
	FRotator rotation = direction.Rotation();
	rotation.Pitch = 0;
	rotation.Roll = 0;

	StareEnemy(rotation);

	FVector location = GetActorLocation() + FVector(0, 0, 45) + towerTurretComponent->GetForwardVector() * 50;

	APooledPlayerTurretBullet* bullet = Cast<APooledPlayerTurretBullet>(
		turretBulletPool->SpawnPooledObject(location, rotation)
	);

	bullet->SetDeactiveTimer(1.5f);



	UGameplayStatics::PlaySoundAtLocation(this, turretFireSound, GetActorLocation(), GetActorRotation());
}

void AItemTurret::SetPositionSucceed(bool value)
{
	isSetSucceed = value;

	UGameplayStatics::PlaySoundAtLocation(this, turretinstallSound, GetActorLocation(), GetActorRotation());

	for (int i = 0; i < originalTowerTurretMaterial.Num(); i++)
	{
		towerTurretComponent->SetMaterial(i, originalTowerTurretMaterial[i]);
	}

	for (int i = 0; i < originalTowerBaseMaterial.Num(); i++)
	{
		towerBaseComponent->SetMaterial(i, originalTowerBaseMaterial[i]);
	}

}

//void AItemTurret::OnBeginOverlapItem(AActor* actor)
//{
//	if (actor && !isSetSucceed)
//	{
//		SetMaterialColor(FVector(1.5, 0.4, 0.4));
//		isCollision = true;
//	}
//}

//void AItemTurret::OnEndOverlapItem(AActor* actor)
//{
//	if (actor && !isSetSucceed)
//	{
//		SetMaterialColor(FVector(0.4, 1.5, 0.4));
//		isCollision = false;
//	}
//}