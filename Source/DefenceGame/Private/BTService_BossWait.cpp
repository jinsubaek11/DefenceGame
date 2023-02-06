#include "BTService_BossWait.h"
#include "PooledBossEnemy.h"
#include "AIController.h"


UBTService_BossWait::UBTService_BossWait()
{
	NodeName = TEXT("Boss Wait");
}

void UBTService_BossWait::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APooledBossEnemy* boss = Cast<APooledBossEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	if (!boss) return;

	if (boss->GetAnimationState() == EBossAnimationState::IDLE) return;
	
	boss->SetAnimationState(EBossAnimationState::IDLE);
}
