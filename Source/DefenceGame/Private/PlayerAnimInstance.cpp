#include "PlayerAnimInstance.h"
#include "GamePlayer.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KismetAnimationLibrary.h"


UPlayerAnimInstance::UPlayerAnimInstance()
{

}

void UPlayerAnimInstance::NativeInitializeAnimation()
{

}

void UPlayerAnimInstance::NativeBeginPlay()
{
	player = Cast<AGamePlayer>(TryGetPawnOwner());
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{	
	if (!player) return;

	FRotator rotation = player->GetActorRotation();
	FVector velocity = player->GetCharacterMovement()->Velocity;

	speed = velocity.Size();
	direction = UKismetAnimationLibrary::CalculateDirection(velocity, rotation);
	isMovingOnGround = player->GetCharacterMovement()->IsMovingOnGround();

	animationState = player->GetAnimationState();
}


void UPlayerAnimInstance::AnimNotify_JumpEnd()
{
	//UE_LOG(LogTemp, Warning, TEXT("AnimNotify_JumpEnd"));
	if (!player) return;	
	
	player->SetAnimationState(EPlayerAnimationState::MOVE);
}
