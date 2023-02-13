#include "FatalTeeth.h"
#include "Components/BoxComponent.h"
#include "PooledWeakEnemy.h"
#include "Tower.h"
#include "GamePlayer.h"
#include "Kismet/GameplayStatics.h"


AFatalTeeth::AFatalTeeth()
{
	att = 3;

	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	boxComponent->SetCollisionProfileName(TEXT("EnemyBulletPreset"));
	SetRootComponent(boxComponent);
}

void AFatalTeeth::BeginPlay()
{
	Super::BeginPlay();

	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AFatalTeeth::OnOverlap);
}

void AFatalTeeth::Shoot()
{
}

void AFatalTeeth::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AGamePlayer* gPlayer = Cast<AGamePlayer>(OtherActor);

	if (gPlayer != nullptr)
	{
		gPlayer->OnTakeDamage(att);
	}

	ATower* aTower = Cast<ATower>(OtherActor);

	if (aTower != nullptr)
	{
		aTower->OnTakeDamage(att);
	}
}
