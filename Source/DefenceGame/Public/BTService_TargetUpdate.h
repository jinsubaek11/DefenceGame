#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_TargetUpdate.generated.h"


UCLASS()
class DEFENCEGAME_API UBTService_TargetUpdate : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_TargetUpdate();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
