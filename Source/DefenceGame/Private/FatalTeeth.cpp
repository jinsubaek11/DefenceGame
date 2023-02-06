// Fill out your copyright notice in the Description page of Project Settings.


#include "FatalTeeth.h"

#include "Components/BoxComponent.h"
#include "PooledWeakEnemy.h"
#include "Tower.h"
#include "GamePlayer.h"


AFatalTeeth::AFatalTeeth()
{
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
	boxComp->SetCollisionProfileName(TEXT("EnemyBulletPreset"));
	
}

void AFatalTeeth::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AFatalTeeth::OnOverlap);


}

void AFatalTeeth::Shoot()
{

}

void AFatalTeeth::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                            UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//�ε��� ����� �÷��̾���
	AGamePlayer* gPlayer = Cast<AGamePlayer>(OtherActor);

	if (gPlayer != nullptr)
	{
		//�÷��̾��� ü���� ���ҽ�Ų��
		gPlayer->OnTakeDamage(teethAttackScore);
	}

	//�ε��� ����� �ݰ���
	ATower* aTower = Cast<ATower>(OtherActor);

	if (aTower != nullptr)
	{
		//�ݰ��� ü���� ���ҽ�Ų��
		aTower->OnTakeTowerDamage(teethAttackScore);
	}

	UE_LOG(LogTemp, Error, TEXT("AFatalTeeth::OnOverlap"));

}
