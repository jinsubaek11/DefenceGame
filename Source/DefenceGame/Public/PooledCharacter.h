#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PooledCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPooledCharacterDespawn, APooledCharacter*, pooledCharacter);

UCLASS()
class DEFENCEGAME_API APooledCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APooledCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	virtual void ResetState() {};

	void SetActive(bool value);
	void SetIndex(int32 index);
	int32 GetIndex() const;
	bool IsActive() const;

public:
	FOnPooledCharacterDespawn OnPooledCharacterDespawn;

private:
	int32 index;
	bool isActive;
};
