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
	//부딪힌 대상이 플레이어라면
	AGamePlayer* gPlayer = Cast<AGamePlayer>(OtherActor);

	if (gPlayer != nullptr)
	{
		//플레이어의 체력을 감소시킨다
		gPlayer->OnTakeDamage(teethAttackScore);
	}

	//부딪힌 대상이 금고라면
	ATower* aTower = Cast<ATower>(OtherActor);

	if (aTower != nullptr)
	{
		//금고의 체력을 감소시킨다
		aTower->OnTakeTowerDamage(teethAttackScore);
	}

	UE_LOG(LogTemp, Error, TEXT("AFatalTeeth::OnOverlap"));

}
