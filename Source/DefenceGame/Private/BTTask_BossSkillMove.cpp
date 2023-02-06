#include "BTTask_BossSkillMove.h"


UBTTask_BossSkillMove::UBTTask_BossSkillMove()
{
	NodeName = TEXT("Boss Skill Move");
}

EBTNodeResult::Type UBTTask_BossSkillMove::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Succeeded;
}