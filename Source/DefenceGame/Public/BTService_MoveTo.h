#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_MoveTo.generated.h"


UCLASS()
class DEFENCEGAME_API UBTService_MoveTo : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_MoveTo();

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
