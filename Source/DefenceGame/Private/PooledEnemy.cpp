#include "PooledEnemy.h"
#include "GamePlayer.h"
#include "EnemyAIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "BrainComponent.h"
#include "EnemyAnimInstance.h"
#include "characterHPWidget.h"
#include "Components/WidgetComponent.h"


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
}

void APooledEnemy::BeginPlay()
{
	Super::BeginPlay();

	UEnemyAnimInstance* enemyAnimInstance = Cast<UEnemyAnimInstance>(GetMesh()->GetAnimInstance());
	if (enemyAnimInstance)
	{
		enemyAnimInstance->OnDeath.AddDynamic(this, &APooledEnemy::OnDeath);
	}
	/*if (!enemyHPwidget) return;
	enemyHPwidget = Cast<UcharacterHPWidget>(enemyHPui->GetWidget());
	enemyHPwidget->SetcharacterHP(enemyHPwidget->charMaxHP);*/
}

void APooledEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APooledEnemy::Attack(AActor* target)
{
	SetAnimationState(EEnemyAnimationState::ATTACK);
}

void APooledEnemy::OnTakeDamage(int32 damage)
{
	hp -= damage;

	if (hp < 0)
	{
		if (aiController)
		{
			aiController->BrainComponent->StopLogic(TEXT("Dead"));
		}
		SetAnimationState(EEnemyAnimationState::DEAD);
		
		FTimerHandle timer;
		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([this] {
			SetActive(false);
		});
		GetWorldTimerManager().SetTimer(timer, timerDelegate, 2.f, false);
	}
	//enemyHPwidget->SetcharacterHP(hp);
}

void APooledEnemy::SetAnimationState(EEnemyAnimationState animState)
{
	animationState = animState;
}

EEnemyAnimationState APooledEnemy::GetAnimationState()
{
	return animationState;
}

void APooledEnemy::Reset()
{

}

void APooledEnemy::SetEnemyState(float health)
{
	hp = health;
}

void APooledEnemy::OnDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("OnDeath"));
	SetActive(false);
}