#include "BTTask_MoveToTarget.h"
#include "EnemyAIController.h"
#include "PooledEnemy.h"


UBTTask_MoveToTarget::UBTTask_MoveToTarget()
{
	NodeName = TEXT("Move To Target");
	
}

EBTNodeResult::Type UBTTask_MoveToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	enemy->SetAnimationState(EEnemyAnimationState::WALK);

	FAIMoveRequest moveRequest;
	moveRequest.SetAllowPartialPath(true);
	moveRequest.SetReachTestIncludesAgentRadius(true);
	moveRequest.SetReachTestIncludesGoalRadius(true);
	moveRequest.SetProjectGoalLocation(true);
	moveRequest.SetGoalLocation(OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()));
	
	OwnerComp.GetAIOwner()->MoveTo(moveRequest);
	//OwnerComp.GetAIOwner()->Set
	enemy->SetAnimationState(EEnemyAnimationState::WALK);

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	//FAIMoveRequest::SetGoalLocation(OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()));
	//FAIMoveRequest::SetGoalLocation()
	return EBTNodeResult::InProgress;
}
