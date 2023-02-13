#include "EnemyToyGun.h"
#include "PooledNormalEnemy.h"
#include "PooledNormalEnemyBullet.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "normalEnemyBulletPool.h"
#include "PooledNormalEnemyBullet.h"


AEnemyToyGun::AEnemyToyGun()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComponent);


	/*toy gunMesh*/
	skeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("gumMesh"));
	

	ConstructorHelpers::FObjectFinder<USkeletalMesh> assetGun(TEXT("/Script/Engine.SkeletalMesh'/Game/Weapons/NewGun/source/RetroGun_01_skel.RetroGun_01_skel'"));

	if (assetGun.Succeeded())
	{		
		skeletalMeshComponent->SetSkeletalMesh(assetGun.Object);
		skeletalMeshComponent->SetupAttachment(RootComponent);
		skeletalMeshComponent->SetRelativeLocationAndRotation(FVector(17, 0, 0), FRotator(90, 0, 180));
		skeletalMeshComponent->SetRelativeScale3D(FVector(0.25f));
	}
}
	
void AEnemyToyGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyToyGun::BeginPlay()
{
	Super::BeginPlay();

	//normalEnemyBulletPool = GetWorld()->SpawnActor<ANormalEnemyBulletPool>();
	Shoot(normalEnemyBulletPool);

}

void AEnemyToyGun::Shoot(AActor* target)
{
	Super::Shoot();

	FVector spawnPosition = GetActorLocation() + GetActorForwardVector();
	FRotator spawnRotator = (target->GetActorLocation() - GetActorLocation()).Rotation();

	FTransform mFireposition = skeletalMeshComponent->GetSocketTransform(TEXT("RetroGun_01FirePosition"));

	APooledNormalEnemyBullet* normalEnemyBullet = Cast<APooledNormalEnemyBullet>(
		normalEnemyBulletPool->SpawnPooledObject(spawnPosition, spawnRotator));

	if (IsValid(normalEnemyBullet))
	{
		normalEnemyBullet->SetDeactiveTimer(1.5f);
	}


}
