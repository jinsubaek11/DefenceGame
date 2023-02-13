#include "EnemyAxe.h"
#include "Tower.h"
#include "GamePlayer.h"
#include "PooledStrongEnemy.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


AEnemyAxe::AEnemyAxe()
{
	att = 10;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	SetRootComponent(boxComponent);
	boxComponent->SetCollisionProfileName(TEXT("EnemyBulletPreset"));

	//axeMesh
	axeMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("axeMeshComp"));

	ConstructorHelpers::FObjectFinder<USkeletalMesh> aMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Weapons/VikingAxe/Hammer_skel.Hammer_skel'"));

	if (aMesh.Succeeded())
	{
		axeMeshComp->SetSkeletalMesh(aMesh.Object);
		axeMeshComp->SetRelativeLocationAndRotation(FVector(-72, 98, -39), FRotator(-24, 79, 0));
		axeMeshComp->SetRelativeScale3D(FVector(0.7));
	}
	if(aMesh.Succeeded())
	{
		axeMeshComp->SetSkeletalMesh(aMesh.Object);
		axeMeshComp->SetupAttachment(RootComponent);
		//axeMeshComp->SetRelativeLocationAndRotation(FVector(-72, 98, -39), FRotator(-24, 79, 0));
		axeMeshComp->SetRelativeLocationAndRotation(FVector(-160, 112, -53), FRotator(-24, 79, 0));
		axeMeshComp->SetRelativeScale3D(FVector(0.7));
	}
}

void AEnemyAxe::BeginPlay()
{
	Super::BeginPlay();

	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyAxe::OnOverlap);
}

void AEnemyAxe::Shoot()
{
}

void AEnemyAxe::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGamePlayer* gPlayer = Cast<AGamePlayer>(OtherActor);
	
	if(gPlayer != nullptr)
	{
		gPlayer->OnTakeDamage(att);
	}
	
	ATower* aTower = Cast<ATower>(OtherActor);
	
	if( aTower != nullptr)
	{
		aTower->OnTakeDamage(att);
	}
}
