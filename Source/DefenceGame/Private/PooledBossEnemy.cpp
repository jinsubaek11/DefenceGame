#include "PooledBossEnemy.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnemyAIController.h"
#include "BossAnimInstance.h"
#include "ArrowBox.h"
#include "Sword.h"
#include "Bow.h"


APooledBossEnemy::APooledBossEnemy()
{
	type = EEnemyType::BOSS;
	hp = 30;
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(140);
	GetCapsuleComponent()->SetCapsuleRadius(40);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Enemy/Boss/Skeleton/boss1.boss1'"));
	if (skeletalMesh.Succeeded())
	{
		USkeletalMeshComponent* meshComponent = GetMesh();
		meshComponent->SetSkeletalMesh(skeletalMesh.Object);
		meshComponent->SetRelativeLocationAndRotation(FVector(0, 15, -140), FRotator(0, -90, 0));
		meshComponent->SetRelativeScale3D(FVector(1.5));
	}

	ConstructorHelpers::FObjectFinder<UMaterialInterface> iconMat(TEXT("/Script/Engine.Material'/Game/UI/Image/M_Boss_Icon.M_Boss_Icon'"));
	if (iconMat.Succeeded())
	{
		planeComponent->SetRelativeScale3D(FVector(5, 5, 2));
		planeComponent->SetMaterial(0, iconMat.Object);
	}
	
	ConstructorHelpers::FClassFinder<AEnemyAIController> bpAIControllerClass(TEXT("/Script/Engine.Blueprint'/Game/Blueprint/BossAI/BP_BossAIController.BP_BossAIController_C'"));
	if (bpAIControllerClass.Succeeded())
	{
		EnemyAIControllerFactory = bpAIControllerClass.Class;
	}

	ConstructorHelpers::FClassFinder<UBossAnimInstance> bpEnemyAnim(TEXT("/Script/Engine.AnimBlueprint'/Game/Enemy/Boss/Animation/ABP_BossAnim.ABP_BossAnim_C'"));
	if (bpEnemyAnim.Succeeded())
	{
		bossAnimFactory = bpEnemyAnim.Class;
		GetMesh()->SetAnimInstanceClass(bossAnimFactory);
	}

	SetEnemyState(hp);
}

void APooledBossEnemy::BeginPlay()
{
	Super::BeginPlay();

	sword = GetWorld()->SpawnActor<ASword>();
	//sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RightHandSocket"));
	sword->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("LeftUpLegSocket"));
	sword->AddActorLocalOffset(FVector(-8, 20, 23));
	sword->AddActorLocalRotation(FRotator(-80, 275, -273));

	bow = GetWorld()->SpawnActor<ABow>();
	bow->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("LeftHandSocket"));
	bow->AddActorLocalOffset(FVector(53, -1.5, -1.8));
	bow->AddActorLocalRotation(FRotator(86, 0, 172));

	arrowBox = GetWorld()->SpawnActor<AArrowBox>();
	arrowBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("SpineSocket"));
	arrowBox->AddActorLocalOffset(FVector(13, 33, -16));
	arrowBox->AddActorLocalRotation(FRotator(0, -22, -80));

	//currentWeapon = sword;
	SetCurrentWeapon(WeaponType::BOW);

	//normalEnemyBulletPool = GetWorld()->SpawnActor<ANormalEnemyBulletPool>();

	FActorSpawnParameters params;
	aiController = GetWorld()->SpawnActor<AEnemyAIController>(EnemyAIControllerFactory, params);
	if (aiController)
	{
		aiController->Possess(this);
	}

	UBossAnimInstance* bossAnim = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (bossAnim)
	{
		bossAnim->OnAttackStart.AddDynamic(this, &APooledBossEnemy::Shoot);
	}

	SetAnimationState(EBossAnimationState::WALKING);
}

void APooledBossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void  APooledBossEnemy::Shoot()
{
	currentWeapon->Shoot();
}

void APooledBossEnemy::Attack(AActor* target)
{
	SetAnimationState(EBossAnimationState::SHOOTING_ARROW);
	targetRotation = (target->GetActorLocation() - GetActorLocation()).Rotation();
}

AWeapon* APooledBossEnemy::GetCurrentWeapon() const
{
	return currentWeapon;
}

EBossAttackType APooledBossEnemy::GetCurrentAttackType() const
{
	return attackBehaviors[currentAttackTypeIndex];
}

WeaponType APooledBossEnemy::GetCurrentWeaponType() const
{
	return currentWeapon->GetWeaponType();
}

EBossAnimationState APooledBossEnemy::GetAnimationState() const
{
	return state;
}

void APooledBossEnemy::SetAnimationState(EBossAnimationState nextState)
{
	state = nextState;
}

bool APooledBossEnemy::GetIsPlayingAnimation() const
{
	return isPlayingAnimation;
}

void APooledBossEnemy::SetIsPlayingAnimation(bool isPlaying)
{
	isPlayingAnimation = isPlaying;
}

FRotator APooledBossEnemy::GetTargetRotation() const
{
	return targetRotation;
}

void APooledBossEnemy::Reset()
{
	SetEnemyState(hp);
}

void APooledBossEnemy::SetCurrentWeapon(WeaponType weaponType)
{
	if (currentWeapon)
	{
		currentWeapon->SetActive(false);
	}

	switch (weaponType)
	{
	case WeaponType::BOW:
		currentWeapon = bow;
		break;
	case WeaponType::SWORD:
		currentWeapon = sword;
		break;
	}

	currentWeapon->SetActive(true);
}
