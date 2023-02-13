// Fill out your copyright notice in the Description page of Project Settings.


#include "FatalTeeth.h"

#include "Components/BoxComponent.h"
#include "PooledWeakEnemy.h"
#include "Tower.h"
#include "GamePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet\KismetSystemLibrary.h"


AFatalTeeth::AFatalTeeth()
{
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComp);
	boxComp->SetCollisionProfileName(TEXT("EnemyBulletPreset"));

	if (!pwEnemy) return;
	boxComp->SetupAttachment(pwEnemy->teethBox);


}

void AFatalTeeth::BeginPlay()
{
	Super::BeginPlay();

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AFatalTeeth::OnOverlap);


}

void AFatalTeeth::Shoot()
{
	pwEnemy = Cast<APooledWeakEnemy>(GetOwner());
	//체력 감소시킬 이빨 공격 하는 타이밍
	if (!pwEnemy) return;
	pwEnemy->SetAnimationState(EEnemyAnimationState::ATTACK);

	pwEnemy->OnTakeDamage(teethAttackScore);


	//TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	//traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel5));

	//TArray<AActor*> ignoreActors;
	//ignoreActors.Init(this, 1);

	//TArray<AActor*> outActors;

	//float radius = 50;

	//
	//FVector mouthLocation = pwEnemy->GetMesh()->GetSocketTransform(TEXT("Head")).GetLocation();// 입 소켓의 위치
	//UClass* seekClass = ATower::StaticClass(); // NULL;
	//UKismetSystemLibrary::SphereOverlapActors(GetWorld(), mouthLocation, radius, traceObjectTypes, seekClass, ignoreActors, outActors);


	//for (AActor* overlappedActor : outActors) {
	//	//UE_LOG(LogTemp, Log, TEXT("OverlappedActor: %s"), *overlappedActor->GetName());
	//	
	//	ATower* aTower = Cast<ATower>(overlappedActor);

	//	if (aTower != nullptr)
	//	{
	//		//금고의 체력을 감소시킨다
	//		aTower->OnTakeTowerDamage(teethAttackScore);
	//	}
	//}


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

}
