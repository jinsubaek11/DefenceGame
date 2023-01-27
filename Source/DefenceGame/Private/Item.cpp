#include "Item.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


AItem::AItem()
{
	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComponent);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnBeginOverlap);
	boxComponent->OnComponentEndOverlap.AddDynamic(this, &AItem::OnEndOverlap);
}

float AItem::GetCoolTime() const
{
	return coolTime;
}

void AItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//OnBeginOverlapItem(OtherActor);

	if (OtherActor && !isSetSucceed)
	{
		SetMaterialColor(FVector(1.5, 0.4, 0.4));
		isCollision = true;
	}
}

void AItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//OnEndOverlapItem(OtherActor);

	if (OtherActor && !isSetSucceed)
	{
		SetMaterialColor(FVector(0.4, 1.5, 0.4));
		isCollision = false;
	}
}

ItemType AItem::GetType() const
{
	return type;
}

bool AItem::GetIsPositionSucceed() const
{
	return isSetSucceed;
}

bool AItem::GetIsCollision() const
{
	return isCollision;
}

void AItem::SetPositionSucceed(bool value)
{

}

void AItem::OnTakeDamage(int32 damage)
{
	hp -= damage;

	if (hp <= 0)
	{
		Destroy();
	}
}

void AItem::OnBeginOverlapItem(AActor* actor)
{

}

void  AItem::OnEndOverlapItem(AActor* actor)
{

}

void AItem::SetMaterialColor(FVector color)
{
	dynamicMaterial->SetVectorParameterValue(TEXT("ColorParameter"), color);
}