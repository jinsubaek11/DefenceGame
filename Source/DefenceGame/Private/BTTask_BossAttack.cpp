#include "BTTask_BossAttack.h"
#include "PooledBossEnemy.h"
#include "GamePlayer.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_BossAttack::UBTTask_BossAttack()
{
	NodeName = TEXT("Boss Attack");
}

EBTNodeResult::Type UBTTask_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	APooledBossEnemy* boss = Cast<APooledBossEnemy>(OwnerComp.GetAIOwner()->GetPawn());
	AActor* target = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));
	if (target)
	{
		boss->Attack(target);

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
