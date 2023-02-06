#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_BossSkillMove.generated.h"


UCLASS()
class DEFENCEGAME_API UBTTask_BossSkillMove : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_BossSkillMove();

private:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
