#include "BTTask_MoveToLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GamePlayer.h"
#include "EnemyAIController.h"
#include "PooledEnemy.h"


UBTTask_MoveToLocation::UBTTask_MoveToLocation()
{
	
}

EBTNodeResult::Type UBTTask_MoveToLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	enemy->SetAnimationState(EEnemyAnimationState::WALK);
	OwnerComp.GetAIOwner()->MoveToLocation(OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()), 300);

	
	return EBTNodeResult::Succeeded;
}

EBTNodeResult::Type UBTTask_MoveToLocation::PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::PerformMoveTask(OwnerComp, NodeMemory);

	OwnerComp.GetAIOwner()->MoveTo(OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()));

	return EBTNodeResult::Succeeded;
}
