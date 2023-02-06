// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAxe.h"
#include "Tower.h"
#include "GamePlayer.h"
#include "PooledStrongEnemy.h"
#include "Components/BoxComponent.h"


AEnemyAxe::AEnemyAxe()
{

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComponent);
	boxComponent->SetCollisionProfileName(TEXT("EnemyBulletPreset"));

	//axeMesh
	axeMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("axeMeshComp"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> aMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Weapons/VikingAxe/Hammer_skel.Hammer_skel'"));

	if(aMesh.Succeeded())
	{
		axeMeshComp->SetSkeletalMesh(aMesh.Object);
		axeMeshComp->SetupAttachment(RootComponent);
		axeMeshComp->SetRelativeLocationAndRotation(FVector(-72, 98, -39), FRotator(-24, 79, 0));
		axeMeshComp->SetRelativeScale3D(FVector(0.7));
	}
}

void AEnemyAxe::BeginPlay()
{
	Super::BeginPlay();

	//collision에 붙인다
	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAxe::OnOverlap);


}

void AEnemyAxe::Shoot()
{
	//애니메이션 휘두르면 공격이 발생
		
	//psEnemy = Cast<APooledStrongEnemy>(GetOwner());
	//if(!psEnemy) return;
	//psEnemy->SetAnimationState(EEnemyAnimationState::ATTACK);

	//psEnemy->OnTakeDamage(axeAttackScore);
}

void AEnemyAxe::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//부딪힌 대상이 플레이어라면
	AGamePlayer* gPlayer = Cast<AGamePlayer>(OtherActor);

	if(gPlayer != nullptr)
	{
		//플레이어의 체력을 감소시킨다
		gPlayer->OnTakeDamage(axeAttackScore);
	}

	//부딪힌 대상이 금고라면
	ATower* aTower = Cast<ATower>(OtherActor);

	if( aTower != nullptr)
	{
		//금고의 체력을 감소시킨다
		aTower->OnTakeTowerDamage(axeAttackScore);
	}

	UE_LOG(LogTemp, Error, TEXT("AEnemyAxe::OnOverlap"));
	
}
