#include "PooledEnemy.h"
#include "GamePlayer.h"
#include "EnemyAIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "BrainComponent.h"
#include "EnemyAnimInstance.h"
#include "BossAnimInstance.h"
#include "Weapon.h"
#include "Components/WidgetComponent.h"
#include "characterHPWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


APooledEnemy::APooledEnemy()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EnemyPreset"));
	planeComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> iconMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (iconMesh.Succeeded())
	{
		planeComponent->SetStaticMesh(iconMesh.Object);
		planeComponent->SetRelativeLocationAndRotation(FVector(0, 0, 3000), FRotator(0, -90, 0));
		planeComponent->SetRelativeScale3D(FVector(3, 3, 2));
		planeComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		//planeComponent->bOnlyOwnerSee = true;
	}

	/*enemyHPui = CreateDefaultSubobject<UWidgetComponent>(TEXT("enemyHPui"));
	enemyHPui->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);	
	enemyHPui->SetWidgetSpace(EWidgetSpace::Screen);
	
	ConstructorHelpers::FClassFinder<UUserWidget> ehpwidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/WBP_characterHPWidget.WBP_characterHPWidget'"));

	if (ehpwidget.Succeeded())
	{
		enemyHPui->SetWidgetClass(ehpwidget.Class);
		enemyHPui->SetRelativeScale3D(FVector(0.3f));
		enemyHPui->SetDrawSize(FVector2D(600, 500));
	}*/

	ConstructorHelpers::FObjectFinder<UMaterialInterface> iconMat(TEXT("/Script/Engine.Material'/Game/UI/Image/M_Enemy_Icon.M_Enemy_Icon'"));
	if (iconMat.Succeeded())
	{
		planeComponent->SetMaterial(0, iconMat.Object);
		planeComponent->CastShadow = false;
	}
	planeComponent->SetupAttachment(RootComponent);

	/*3d Sound*/
	soundDistance = CreateDefaultSubobject<USoundAttenuation>(TEXT("soundDistance"));
	ConstructorHelpers::FObjectFinder<USoundAttenuation> soundDist(TEXT("/Script/Engine.SoundAttenuation'/Game/Sound/SoundEffects/WeakEnemy_attenuation.WeakEnemy_attenuation'"));
	if (soundDist.Succeeded())
	{
		soundDistance = (soundDist.Object);
	}
	
	hpWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Hp Widget Component"));
	hpWidgetComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	hpWidgetComponent->SetRelativeLocationAndRotation(FVector(0, 0, 130), FRotator(0, 0, 0));
	hpWidgetComponent->SetWidgetSpace(EWidgetSpace::World);

	ConstructorHelpers::FClassFinder<UcharacterHPWidget> hpWidgetAsset(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprint/WBP_characterHPWidget.WBP_characterHPWidget_C'"));

	if (hpWidgetAsset.Succeeded())
	{
		hpWidgetComponent->SetWidgetClass(hpWidgetAsset.Class);
		hpWidgetComponent->SetRelativeLocationAndRotation(FVector(0, 0, 110), FRotator(0, 0, 0));
		hpWidgetComponent->SetRelativeScale3D(FVector(0.3f));
		hpWidgetComponent->SetDrawSize(FVector2D(600, 500));
	}
}

void APooledEnemy::BeginPlay()
{
	Super::BeginPlay();

	UEnemyAnimInstance* enemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (enemyAnimInstance)
	{
		enemyAnimInstance->OnDeath.AddDynamic(this, &APooledEnemy::OnDeath);
	}

	UBossAnimInstance* bossAnimInstance = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (bossAnimInstance)
	{
		bossAnimInstance->OnDeath.AddDynamic(this, &APooledEnemy::OnDeath);
	}


	hpWidget = Cast<UcharacterHPWidget>(hpWidgetComponent->GetWidget());

	if (hpWidget)
	{
		hpWidget->ShowHPBar(hp, maxHp);
	}
}

void APooledEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerCameraManager* cm = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);

	FRotator newRotation = UKismetMathLibrary::MakeRotFromXZ(
		cm->GetCameraLocation() - GetActorLocation(), GetActorUpVector()
	);

	hpWidgetComponent->SetWorldRotation(newRotation);
}

void APooledEnemy::Attack(AActor* target)
{
	SetAnimationState(EEnemyAnimationState::ATTACK);
}

void APooledEnemy::OnTakeDamage(int32 damage)
{
	hp -= damage;

	if (hp <= 0)
	{
		hp = 0;
		if (!aiController) return;

		aiController->BrainComponent->StopLogic(TEXT("Dead"));

		if (type == EEnemyType::ENEMY)
		{
			SetAnimationState(EEnemyAnimationState::DEAD);
		}
		else
		{
			SetAnimationState(EBossAnimationState::DEATH);
		}
	}

	hpWidget->ShowHPBar(hp, maxHp);
}

void APooledEnemy::SetAnimationState(EEnemyAnimationState animState)
{
	animationState = animState;
}

EEnemyAnimationState APooledEnemy::GetAnimationState()
{
	return animationState;
}

void APooledEnemy::ResetState()
{
	SetEnemyState(maxHp);
	hpWidget->ShowHPBar(hp, maxHp);
	aiController->BrainComponent->RestartLogic();
}

void APooledEnemy::SetEnemyState(float health)
{
	hp = health;
	maxHp = health;
}

void APooledEnemy::Upgrade()
{
	SetEnemyState(maxHp += 10);
}

void APooledEnemy::OnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("OnDeath"));
	SetActorEnableCollision(false);
	SetActive(false);
	ResetState();
}

