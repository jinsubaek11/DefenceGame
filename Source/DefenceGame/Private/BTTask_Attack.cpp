#include "BTTask_Attack.h"
#include "GamePlayer.h"
#include "PooledEnemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Item.h"
#include "Tower.h"


UBTTask_Attack::UBTTask_Attack()
{
	NodeName = TEXT("Attack");
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APooledEnemy* enemy = Cast<APooledEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (target)
	{
		enemy->Attack(target);
		enemy->SetAnimationState(EEnemyAnimationState::ATTACK);

		return EBTNodeResult::Succeeded;
	}

	enemy->SetAnimationState(EEnemyAnimationState::WALK);
	return EBTNodeResult::Failed;
}

