#include "BTService_MoveTo.h"
#include "PooledEnemy.h"
#include "AIController.h"


UBTService_MoveTo::UBTService_MoveTo()
{
	NodeName = TEXT("Service MoveTo");
}

void UBTService_MoveTo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (enemy)
	{
		enemy->SetAnimationState(EEnemyAnimationState::WALK);
	}
}
