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
	hp = 500;
	
	GetCapsuleComponent()->SetCapsuleHalfHeight(170);
	GetCapsuleComponent()->SetCapsuleRadius(40);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Enemy/Boss/Skeleton/boss1.boss1'"));
	if (skeletalMesh.Succeeded())
	{
		USkeletalMeshComponent* meshComponent = GetMesh();
		meshComponent->SetSkeletalMesh(skeletalMesh.Object);
		meshComponent->SetRelativeLocationAndRotation(FVector(0, 15, -170), FRotator(0, -90, 0));
		meshComponent->SetRelativeScale3D(FVector(1.5));
	}

	//meshComponent->SetupAttachment(GetMesh(), TEXT("RightHandSocket"));
	
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

	for (int i = 0; i < 30; i++)
	{
		float rand = FMath::RandRange(0, 3);
		rand = 3;
		attackBehaviors.Emplace((EBossAttackType)rand);
	}

	UE_LOG(LogTemp, Warning, TEXT("%d"), attackBehaviors.Num());

	UBossAnimInstance* bossAnim = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());
	if (bossAnim)
	{
		bossAnim->OnAttackStart.AddDynamic(this, &APooledBossEnemy::Shoot);
	}
}

void APooledBossEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void  APooledBossEnemy::Shoot()
{
	UE_LOG(LogTemp, Warning, TEXT("APooledBossEnemy::Shoot"));
	currentWeapon->Shoot();
}

void APooledBossEnemy::Attack(AActor* target, EBossAttackType attackType)
{
	if (isPlayingAnimation) return;

	switch (attackType)
	{
	case EBossAttackType::SWORD_INWARD_SLASH:
		SetAnimationState(EBossAnimationState::SWORD_INWARD_SLASH);
		break;
	case EBossAttackType::SWORD_OUTWARD_SLASH:
		SetAnimationState(EBossAnimationState::SWORD_OUTWARD_SLASH);
		break;
	case EBossAttackType::SWORD_COMBO:
		SetAnimationState(EBossAnimationState::SWORD_COMBO);
		break;
	case EBossAttackType::SHOOTING_ARROW:
		SetAnimationState(EBossAnimationState::SHOOTING_ARROW);
		targetRotation = (target->GetActorLocation() - GetActorLocation()).Rotation();
		break;
//	case EBossAttackType::JUMP_ATTACK:
		//SetAnimationState(EBossAnimationState::JUMP_ATTACK);
	//	break;
	}

	SetIsPlayingAnimation(true);

	currentAttackTypeIndex = (++currentAttackTypeIndex) % attackBehaviors.Num();
	UE_LOG(LogTemp, Warning, TEXT("%d"), currentAttackTypeIndex);
	//Super::Attack(target);

	//FVector spawnPosition = GetActorLocation() + GetActorForwardVector();
	//FRotator spawnRotator = (target->GetActorLocation() - GetActorLocation()).Rotation();

	//APooledNormalEnemyBullet* normalEnemyBullet = Cast<APooledNormalEnemyBullet>(
	//	normalEnemyBulletPool->SpawnPooledObject(spawnPosition, spawnRotator));

	//if (IsValid(normalEnemyBullet))
	//{
	//	normalEnemyBullet->SetDeactiveTimer(1.5f);
	//}
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

