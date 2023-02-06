// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyToyGun.h"
#include "PooledNormalEnemy.h"
#include "PooledNormalEnemyBullet.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

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

void AEnemyToyGun::Shoot()
{
	Super::Shoot();

	if (bulletCounts <= 0)
	{		
		return;
	}

	FVector start;
	FRotator rotation;
	pNormalEnemy->GetController()->GetPlayerViewPoint(start, rotation);
	FVector end = start + rotation.Vector() * attackRange;


	FVector spawnPosition = GetActorLocation() + GetActorForwardVector();
	FRotator spawnRotator = (pNormalEnemy->GetActorLocation() - GetActorLocation()).Rotation();
	FTransform mFireposition = skeletalMeshComponent->GetSocketTransform(TEXT("RetroGun_01FirePosition"));


	APooledNormalEnemyBullet* normalEnemyBullet = GetWorld()->SpawnActor<APooledNormalEnemyBullet>(nEnemyBulletPool, mFireposition.GetLocation(), spawnRotator);

	if (IsValid(normalEnemyBullet))
	{
		normalEnemyBullet->SetDeactiveTimer(1.5f);
	}

	//emmiter 위치 조정?
	UGameplayStatics::SpawnEmitterAttached(muzzleFlash, skeletalMeshComponent, TEXT("RetroGun_01FirePosition"));


}
