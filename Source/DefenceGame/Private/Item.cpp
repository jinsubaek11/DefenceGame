#include "Item.h"
#include "PooledBullet.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "characterHPWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


AItem::AItem()
{
	boxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	SetRootComponent(boxComponent);

	hpWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Hp Widget Component"));
	hpWidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	hpWidgetComponent->SetRelativeLocationAndRotation(FVector(0, 0, 130), FRotator(0, 0, 0));
	hpWidgetComponent->SetWidgetSpace(EWidgetSpace::World);

	ConstructorHelpers::FClassFinder<UcharacterHPWidget> hpWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/WBP_characterHPWidget.WBP_characterHPWidget_C'"));

	if (hpWidgetAsset.Succeeded())
	{
		hpWidgetComponent->SetWidgetClass(hpWidgetAsset.Class);
		hpWidgetComponent->SetRelativeLocationAndRotation(FVector(0, 0, 110), FRotator(0, 180, 0));
		hpWidgetComponent->SetRelativeScale3D(FVector(0.3f));
		hpWidgetComponent->SetDrawSize(FVector2D(600, 500));
	}
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	boxComponent->OnComponentBeginOverlap.AddDynamic(this, &AItem::OnBeginOverlap);
	boxComponent->OnComponentEndOverlap.AddDynamic(this, &AItem::OnEndOverlap);

	hpWidget = Cast<UcharacterHPWidget>(hpWidgetComponent->GetWidget());

	if (hpWidget)
	{
		hpWidget->ShowHPBar(hp, maxHp);
	}
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerCameraManager* cm = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	FRotator newRotation = UKismetMathLibrary::MakeRotFromXZ(
		cm->GetCameraLocation() - GetActorLocation(), GetActorUpVector()
	);

	hpWidgetComponent->SetWorldRotation(newRotation);
}

float AItem::GetCoolTime() const
{
	return coolTime;
}

void AItem::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//OnBeginOverlapItem(OtherActor);

	APooledBullet* bullet = Cast<APooledBullet>(OtherActor);
	if (bullet) return;

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
		hp = 0;
		Destroy();
	}

	hpWidget->ShowHPBar(hp, maxHp);
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