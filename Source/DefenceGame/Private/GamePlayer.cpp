#include "GamePlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <GameFramework/Controller.h>
#include <Camera/CameraComponent.h>
#include "NormalEnemyPool.h"
#include "PooledCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GamePlayerCameraManager.h"
#include "ItemObstacle.h"
#include "ItemTurret.h"
#include "Item.h"
#include "HandGrenade.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Rifle.h"
#include "Bazooka.h"
#include "Weapon.h"
#include "GamePlayerUI.h"
#include "Kismet/GameplayStatics.h"
#include "DefenceGameMode.h"
#include "MainUI.h"
#include "CircularProgressBar.h"


AGamePlayer::AGamePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Player/Skeleton/Player.Player'"));
	if (mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(mesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
		GetMesh()->bReceivesDecals = false;
	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerPreset"));

	springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	springArmComponent->SetupAttachment(RootComponent);
	springArmComponent->SetRelativeLocation(FVector(0, 70, 90));
	springArmComponent->TargetArmLength = 400;
	springArmComponent->bUsePawnControlRotation = true;
	
	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	cameraComponent->SetupAttachment(springArmComponent);

	planeComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Plane Component"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> iconMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Plane.Plane'"));
	if (iconMesh.Succeeded())
	{
		planeComponent->SetStaticMesh(iconMesh.Object);
		planeComponent->SetRelativeLocationAndRotation(FVector(0, 0, 3000), FRotator(0, 0, 0));
		planeComponent->SetRelativeScale3D(FVector(10, 10, 2));
		planeComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	ConstructorHelpers::FObjectFinder<UMaterialInterface> iconMat(TEXT("/Script/Engine.Material'/Game/UI/Image/M_Player_Icon.M_Player_Icon'"));
	if (iconMat.Succeeded())
	{
		planeComponent->SetMaterial(0, iconMat.Object);
		planeComponent->CastShadow = false;
	}
	planeComponent->SetupAttachment(RootComponent);
}

void AGamePlayer::BeginPlay()
{
	Super::BeginPlay();

	playerUI = Cast<AGamePlayerUI>(UGameplayStatics::GetActorOfClass(GetWorld(), AGamePlayerUI::StaticClass()));
	if (playerUI)
	{
		playerUI->SetAnimationState(EPlayerUIAnimationState::IDLE);
	}

	animationState = EPlayerAnimationState::MOVE;

	rifle = GetWorld()->SpawnActor<ARifle>();
	rifle->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RifleSocket"));
	bazooka = GetWorld()->SpawnActor<ABazooka>();
	bazooka->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RifleSocket"));
	handGrenade = GetWorld()->SpawnActor<AHandGrenade>();
	handGrenade->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RifleSocket"));

	currentWeapon = Cast<AWeapon>(rifle);
	
	gameMode = Cast<ADefenceGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void AGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (obstacleRemainingTime > 0)
	{
		second += DeltaTime;
		obstacleRemainingTime -= DeltaTime;

		if (second >= 1.f && currentItemType == ItemType::OBSTACLE)
		{
			gameMode->mainUIWidget->PrintItemRemainingTime(
				obstacleRemainingTime, itemCoolTime
			);

			second = 0.f;
		}
	}

	if (turretRemainingTime > 0)
	{
		second += DeltaTime;
		turretRemainingTime -= DeltaTime;

		if (second >= 1.f && currentItemType == ItemType::TURRET)
		{
			gameMode->mainUIWidget->PrintItemRemainingTime(
				turretRemainingTime, itemCoolTime
			);

			second = 0.f;
		}
	}


	if (isItemMode && newItem)
	{
		CheckEnableItemPosition(*newItem);
		return;
	}

	if (!isShoot) return;
	if (!currentWeapon) return;

	if (currentWeapon->GetWeaponType() == WeaponType::RIFLE)
	{
		currentWeapon->Shoot();
		if (gameMode->mainUIWidget)
		{
			gameMode->mainUIWidget->PrintBulletCount(
				currentWeapon->GetBulletCounts(), currentWeapon->GetMaxBulletCounts()
			);
		}
		isShoot = false;

		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([this] {
			SetAnimationState(EPlayerAnimationState::MOVE);
			GetWorldTimerManager().ClearTimer(animationTimer);
		});
		GetWorldTimerManager().SetTimer(animationTimer, timerDelegate, 0.25f, false);

		return;
	}

	if (isAttackEnable)
	{
		currentWeapon->Shoot();
		if (gameMode->mainUIWidget)
		{
			gameMode->mainUIWidget->PrintBulletCount(
				currentWeapon->GetBulletCounts(), currentWeapon->GetMaxBulletCounts()
			);
		}
		isAttackEnable = false;
	}
}

void AGamePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("LookUp", this, &AGamePlayer::OnAxisLookUp);
	PlayerInputComponent->BindAxis("TurnRight", this, &AGamePlayer::OnAxisTurnRight);
	PlayerInputComponent->BindAxis("MoveForward", this, &AGamePlayer::OnAxisMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGamePlayer::OnAxisMoveRight);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionJump);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionClick);
	PlayerInputComponent->BindAction<FInputSwitchWeapon>("UseRifle", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionSwitchWeapon, 1);
	PlayerInputComponent->BindAction<FInputSwitchWeapon>("UseBazooka", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionSwitchWeapon, 2);
	PlayerInputComponent->BindAction<FInputSwitchWeapon>("UseHandGrenade", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionSwitchWeapon, 3);
	PlayerInputComponent->BindAction<FInputSwitchItem>("UseObstacle", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionUseItemMode, 1);
	PlayerInputComponent->BindAction<FInputSwitchItem>("UseTurret", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionUseItemMode, 2);
	PlayerInputComponent->BindAction("ReLoad", EInputEvent::IE_Pressed, this, &AGamePlayer::OnActionReLoad);
}

void AGamePlayer::OnTakeDamage(float damage)
{
	hp -= damage;

	gameMode->mainUIWidget->HealthBar->PrintCurrentHealth((int)hp, (int)maxHp);

	if (hp <= 0)
	{
		hp = 0;
		gameMode->mainUIWidget->HealthBar->PrintCurrentHealth((int)hp, (int)maxHp);

		playerUI->SetAnimationState(EPlayerUIAnimationState::DEAD);
		SetAnimationState(EPlayerAnimationState::DEAD);

		FTimerHandle timer;
		FTimerDelegate timerDelegate;
		timerDelegate.BindLambda([this] {
			gameMode->ShowGameOverScreen();
		});

		GetWorldTimerManager().SetTimer(timer, timerDelegate, 2.f, false);

		return;
	}

	playerUI->SetAnimationState(EPlayerUIAnimationState::HIT);
	UPlayerUIAnim* playerUIAnim = Cast<UPlayerUIAnim>(playerUI->GetMesh()->GetAnimInstance());
	if (playerUIAnim)
	{
		int rand = FMath::RandRange(1, 2);
		FName sectionName = FName(FString("Hit") + FString::FormatAsNumber(rand));
		playerUIAnim->PlayHitAnimation(sectionName);
	}
}

void AGamePlayer::SetAttackAnimation(WeaponType weaponType)
{
	switch (weaponType)
	{
	case WeaponType::RIFLE:
		SetAnimationState(EPlayerAnimationState::SHOOT_RIFLE);
		break;
	case WeaponType::BAZOOKA:
		SetAnimationState(EPlayerAnimationState::SHOOT_BAZOOKA);
		break;
	case WeaponType::HAND_GRENADE:
		SetAnimationState(EPlayerAnimationState::SHOOT_GRENADE);
		break;
	}

	SetIsShoot(true);
}

void AGamePlayer::SetAttackEnable(bool value)
{
	isAttackEnable = value;
}

void AGamePlayer::SetAttackMode(bool isAttackMode)
{
	if (isAttackMode)
	{
		ClearItem();
		isItemMode = false;

		return;
	}

	isItemMode = true;
	rifle->SetActive(false);
	bazooka->SetActive(false);
	handGrenade->SetActive(false);
	currentWeapon = nullptr;
}

void AGamePlayer::SetIsShoot(bool value)
{
	isShoot = value;
}

void AGamePlayer::SetAnimationState(EPlayerAnimationState state)
{
	if (animationState == state) return;

	animationState = state;
}

EPlayerAnimationState AGamePlayer::GetAnimationState()
{
	return animationState;
}

void AGamePlayer::OnAxisLookUp(float value)
{
	//if (isItemMode) return;

	AddControllerPitchInput(value * 0.3);
}

void AGamePlayer::OnAxisTurnRight(float value)
{
	//if (isItemMode) return;

	AddControllerYawInput(value * 0.3);
}

void AGamePlayer::OnAxisMoveForward(float value)
{
	FVector axisX = FVector(value, 0, 0).RotateAngleAxis(
		GetControlRotation().Yaw, FVector(0, 0, 1)
	);

	AddMovementInput(axisX);
}

void AGamePlayer::OnAxisMoveRight(float value)
{
	FVector axisY = FVector(0, value, 0).RotateAngleAxis(
		GetControlRotation().Yaw, FVector(0, 0, 1)
	);

	AddMovementInput(axisY);
}

void AGamePlayer::OnActionClick()
{
	if (isItemMode)
	{
		if (!newItem) return;
		if (newItem->GetType() == ItemType::OBSTACLE && obstacleRemainingTime > 0) return;
		if (newItem->GetType() == ItemType::TURRET && turretRemainingTime > 0) return;

		if (!newItem->GetIsPositionSucceed() && !newItem->GetIsCollision())
		{			
			if (newItem->GetType() == ItemType::OBSTACLE)
			{
				obstacleRemainingTime = newItem->GetCoolTime();
				itemCoolTime = obstacleRemainingTime;
			}
			else
			{
				turretRemainingTime = newItem->GetCoolTime();
				itemCoolTime = turretRemainingTime;
			}

			newItem->SetPositionSucceed(true);
			items.Add(newItem);
			newItem = nullptr;
			isItemMode = false;
			currentWeapon = rifle;
		}

		return;
	}

	if (currentWeapon && currentWeapon->HasRemainBullet())
	{
		SetAttackAnimation(currentWeapon->GetWeaponType());
	}
}

void AGamePlayer::OnActionUseItemMode(int32 itemIndex)
{
	ClearItem();

	//newObstacle = GetWorld()->SpawnActor<AItemObstacle>(GetActorLocation() + GetActorForwardVector() * 300, GetActorRotation());
	//currentWeapon->SetActive(false);
	SetAttackMode(false);

	FVector itemLocation = GetActorLocation() + GetActorForwardVector() * 300;
	FRotator itemRotation = GetActorRotation();
	
	switch ((ItemType)itemIndex)
	{
	case ItemType::OBSTACLE:
		newItem = GetWorld()->SpawnActor<AItemObstacle>(itemLocation, itemRotation);
		break;
	case ItemType::TURRET:
		itemLocation.Z = 55;
		newItem = GetWorld()->SpawnActor<AItemTurret>(itemLocation, itemRotation);
		break;
	}

	currentItemType = newItem->GetType();

	if (gameMode->mainUIWidget)
	{
		gameMode->mainUIWidget->SetCurrentItemImage(gameMode, currentItemType);

		//if (obstacleRemainingTime > 0 || turretRemainingTime > 0) return;

		gameMode->mainUIWidget->PrintItemRemainingTime(
			newItem->GetCoolTime(), newItem->GetCoolTime()
		);
	}
}

void AGamePlayer::OnActionJump()
{
	if (animationState == EPlayerAnimationState::JUMP) return;

	SetAnimationState(EPlayerAnimationState::JUMP);
	Jump();
}


void AGamePlayer::OnActionSwitchWeapon(int32 weaponIndex)
{
	if (isShoot) return;
	UE_LOG(LogTemp, Warning, TEXT("OnActionSwitchWeapon"));
	
	if (currentWeapon)
	{
		if (currentWeapon->GetWeaponType() == (WeaponType)weaponIndex) return;

		if (currentWeapon->GetWeaponType() == WeaponType::HAND_GRENADE)
		{
			AHandGrenade* castCurrentWeapon = Cast<AHandGrenade>(currentWeapon);
			if (castCurrentWeapon->GetIsExploded() || !castCurrentWeapon->GetIsShootStart())
			{
				currentWeapon->SetActive(false);
			}

			castCurrentWeapon = nullptr;
		}
		else
		{
			currentWeapon->SetActive(false);

		}
	}
	SetAttackMode(true);

	switch ((WeaponType)weaponIndex)
	{
	case WeaponType::RIFLE:
		currentWeapon = Cast<AWeapon>(rifle);
		break;
	case WeaponType::BAZOOKA:
		currentWeapon = Cast<AWeapon>(bazooka);
		break;
	case WeaponType::HAND_GRENADE:
		currentWeapon = Cast<AWeapon>(handGrenade);
		break;
	}

	if (gameMode->mainUIWidget)
	{
		gameMode->mainUIWidget->SetCurrentWeaponImage(gameMode, currentWeapon->GetWeaponType());

		gameMode->mainUIWidget->PrintBulletCount(
			currentWeapon->GetBulletCounts(), currentWeapon->GetMaxBulletCounts()
		);
	}

	if (currentWeapon->GetWeaponType() == WeaponType::HAND_GRENADE)
	{
		AHandGrenade* castCurrentWeapon = Cast<AHandGrenade>(currentWeapon);
		if (castCurrentWeapon->GetIsExploded()) return;
	}
	
	currentWeapon->SetActive(true);


}

void AGamePlayer::OnActionReLoad()
{
	if (isItemMode) return;

	currentWeapon->ReLoad();

	if (gameMode->mainUIWidget)
	{
		gameMode->mainUIWidget->PrintBulletCount(
			currentWeapon->GetBulletCounts(), currentWeapon->GetMaxBulletCounts()
		);
	}
}

void AGamePlayer::CheckEnableItemPosition(AItem& item)
{
	newItem->SetActorRotation(GetActorRotation());
	FVector location = GetActorLocation() + GetActorForwardVector() * 400;

	switch (item.GetType())
	{
	case ItemType::OBSTACLE:
		newItem->SetActorLocation(location);
		break;
	case ItemType::TURRET:
		location.Z = 55;
		newItem->SetActorLocation(location);
		break;
	}
}

void AGamePlayer::ClearItem()
{
	if (newItem)
	{
		newItem->Destroy();
		newItem = nullptr;
	};
}