#include "Item.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnBeginOverlap);
	boxComponent->OnComponentEndOverlap.AddDynamic(this, &AItem::OnEndOverlap);
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OnBeginOverlapItem(OtherActor);
}

void AItem::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OnEndOverlapItem(OtherActor);
}

void AItem::OnBeginOverlapItem(AActor* OtherActor)
{

}

void AItem::OnEndOverlapItem(AActor* OtherActor)
{

}

bool AItem::GetIsPositionSucceed()
{
	return isSetSucceed;
}

bool AItem::GetIsCollision()
{
	return isCollision;
}

void AItem::SetPositionSucceed(bool value)
{
	isSetSucceed = value;
	for (int i = 0; i < originalMaterial.Num(); i++)
	{
		meshComponent->SetMaterial(i, originalMaterial[i]);
	}
}

void AItem::SetMaterialColor(FVector color)
{
	dynamicMaterial->SetVectorParameterValue(TEXT("ColorParameter"), color);
}