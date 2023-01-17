#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToLocation.generated.h"


UCLASS()
class DEFENCEGAME_API UBTTask_MoveToLocation : public UBTTask_MoveTo
{
	GENERATED_BODY()
	
public:
	UBTTask_MoveToLocation();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual EBTNodeResult::Type PerformMoveTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);

};
