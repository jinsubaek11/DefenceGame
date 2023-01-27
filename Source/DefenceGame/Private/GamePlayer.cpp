#include "GamePlayer.h"
#include <GameFramework/SpringArmComponent.h>
#include "GameFramework/CharacterMovementComponent.h"
#include <GameFramework/Controller.h>
#include <Camera/CameraComponent.h>
#include "NormalEnemyPool.h"
#include "PooledCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GamePlayerCameraManager.h"
#include "ItemObstacle.h"
#include "ItemTurret.h"
#include "Item.h"
#include "HandGrenade.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Rifle.h"
#include "Bazooka.h"
#include "Weapon.h"


AGamePlayer::AGamePlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> mesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Player/Skeleton/Player.Player'"));
	if (mesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(mesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));
	}

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("PlayerPreset"));

	springArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	springArmComponent->SetupAttachment(RootComponent);
	springArmComponent->SetRelativeLocation(FVector(0, 70, 90));
	springArmComponent->TargetArmLength = 400;
	springArmComponent->bUsePawnControlRotation = true;
	
	cameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	cameraComponent->SetupAttachment(springArmComponent);


	GetCharacterMovement()->bOrientRotationToMovement = true;


}

void AGamePlayer::BeginPlay()
{
	Super::BeginPlay();

	animationState = EPlayerAnimationState::MOVE;

	rifle = GetWorld()->SpawnActor<ARifle>();
	rifle->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RifleSocket"));
	bazooka = GetWorld()->SpawnActor<ABazooka>();
	bazooka->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RifleSocket"));
	handGrenade = GetWorld()->SpawnActor<AHandGrenade>();
	handGrenade->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("RifleSocket"));

	currentWeapon = Cast<AWeapon>(rifle);
	//GetActorLocation() + GetActorForwardVector() * 300, GetActorRotation()

	//isItemMode = true;
}

void AGamePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (obstacleRemainingTime > 0)
	{
		obstacleRemainingTime -= DeltaTime;
	}

	if (turretRemainingTime > 0)
	{
		turretRemainingTime -= DeltaTime;
	}

	if (isItemMode && newItem)
	{
		CheckEnableItemPosition(*newItem);
		return;
	}

	if (!isShoot) return;

	if (currentWeapon->GetWeaponType() == WeaponType::RIFLE)
	{
		currentWeapon->Shoot();
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

	UE_LOG(LogTemp, Warning, TEXT("%f"), hp);
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
			}
			else
			{
				turretRemainingTime = newItem->GetCoolTime();
			}

			newItem->SetPositionSucceed(true);
			items.Add(newItem);
			newItem = nullptr;
			isItemMode = false;
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