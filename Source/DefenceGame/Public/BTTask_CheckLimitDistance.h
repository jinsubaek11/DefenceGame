#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTask_CheckLimitDistance.generated.h"


UCLASS()
class DEFENCEGAME_API UBTTask_CheckLimitDistance : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTTask_CheckLimitDistance();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
