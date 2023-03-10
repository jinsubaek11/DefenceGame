#include "BTService_BossMoveTo.h"
#include "PooledBossEnemy.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTService_BossMoveTo::UBTService_BossMoveTo()
{
	NodeName = TEXT("Boss MoveTo");
}


void UBTService_BossMoveTo::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APooledBossEnemy* boss = Cast<APooledBossEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (!boss) return;

	boss->SetAnimationState(EBossAnimationState::WALKING);
}
