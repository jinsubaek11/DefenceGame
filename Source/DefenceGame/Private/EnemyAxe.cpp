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

	//collision�� ���δ�
	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAxe::OnOverlap);


}

void AEnemyAxe::Shoot()
{
	//�ִϸ��̼� �ֵθ��� ������ �߻�
		
	//psEnemy = Cast<APooledStrongEnemy>(GetOwner());
	//if(!psEnemy) return;
	//psEnemy->SetAnimationState(EEnemyAnimationState::ATTACK);

	//psEnemy->OnTakeDamage(axeAttackScore);
}

void AEnemyAxe::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//�ε��� ����� �÷��̾���
	AGamePlayer* gPlayer = Cast<AGamePlayer>(OtherActor);

	if(gPlayer != nullptr)
	{
		//�÷��̾��� ü���� ���ҽ�Ų��
		gPlayer->OnTakeDamage(axeAttackScore);
	}

	//�ε��� ����� �ݰ���
	ATower* aTower = Cast<ATower>(OtherActor);

	if( aTower != nullptr)
	{
		//�ݰ��� ü���� ���ҽ�Ų��
		aTower->OnTakeTowerDamage(axeAttackScore);
	}

	UE_LOG(LogTemp, Error, TEXT("AEnemyAxe::OnOverlap"));
	
}
