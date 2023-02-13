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
	//ü�� ���ҽ�ų �̻� ���� �ϴ� Ÿ�̹�
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
	//FVector mouthLocation = pwEnemy->GetMesh()->GetSocketTransform(TEXT("Head")).GetLocation();// �� ������ ��ġ
	//UClass* seekClass = ATower::StaticClass(); // NULL;
	//UKismetSystemLibrary::SphereOverlapActors(GetWorld(), mouthLocation, radius, traceObjectTypes, seekClass, ignoreActors, outActors);


	//for (AActor* overlappedActor : outActors) {
	//	//UE_LOG(LogTemp, Log, TEXT("OverlappedActor: %s"), *overlappedActor->GetName());
	//	
	//	ATower* aTower = Cast<ATower>(overlappedActor);

	//	if (aTower != nullptr)
	//	{
	//		//�ݰ��� ü���� ���ҽ�Ų��
	//		aTower->OnTakeTowerDamage(teethAttackScore);
	//	}
	//}


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

}
