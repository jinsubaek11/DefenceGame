#include "Weapon.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GamePlayer.h"

AWeapon::AWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	player = Cast<AGamePlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::Shoot()
{
	if (!player) return;

	bulletCounts--;
}

void AWeapon::ReLoad()
{
	if (!player) return;

	bulletCounts = maxBulletCounts;
}

void AWeapon::SetActive(bool value)
{
	SetActorHiddenInGame(!value);
	SetActorEnableCollision(value);
	SetActorTickEnabled(value);
}

int32 AWeapon::GetBulletCounts() const
{
	return bulletCounts;
}

int32 AWeapon::GetMaxBulletCounts() const
{
	return maxBulletCounts;
}

bool AWeapon::HasRemainBullet() const
{
	return bulletCounts > 0;
}

WeaponType AWeapon::GetWeaponType() const
{
	return weaponType;
}

void AWeapon::DrawWeaponRange()
{
	if (!player) return;

	FVector start;
	FRotator rotation;
	player->GetController()->GetPlayerViewPoint(start, rotation);
	FVector end = start + rotation.Vector() * attackRange;

	FVector traceLine = end - start;
	FVector startFromPlayer = player->GetActorLocation() - start;
	FVector playerProjectOnToTraceLine = startFromPlayer.ProjectOnTo(traceLine);
	autoDestroyRange = attackRange - playerProjectOnToTraceLine.Length();

	FVector decalSize = FVector(autoDestroyRange * 0.5, 20, 10);
	FVector decalLocation = player->GetActorLocation() + player->GetActorForwardVector() * decalSize.X;

	FHitResult hitResult;
	FCollisionQueryParams params;
	params.AddIgnoredActor(player);

	bool isHit = GetWorld()->LineTraceSingleByChannel(
		hitResult, start, end, ECollisionChannel::ECC_Visibility, params
	);

	if (isHit)
	{
		dynamicMaterial->SetVectorParameterValue(TEXT("DistCheckParam"), FVector(0.1, 1, 0.1));
		//DrawDebugLine(GetWorld(), start, end, FColor::Red);
	}
	else
	{
		dynamicMaterial->SetVectorParameterValue(TEXT("DistCheckParam"), FVector(1, 1, 1));
	}

	decalLocation += player->GetActorRightVector() * 45;
	decalLocation.Z = 0;
	decalComponent->DecalSize = decalSize;
	decalComponent->SetWorldLocation(decalLocation);
	decalComponent->SetWorldRotation(decalRotation);
	decalComponent->SetVisibility(true);
}