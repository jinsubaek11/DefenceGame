#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CircularProgressBar.generated.h"


UCLASS()
class DEFENCEGAME_API UCircularProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

public:
	void PrintCurrentHealth(int currentHp, int maxHp);

public:
	UPROPERTY(EditDefaultsOnly, meta = (bindwidget))
	class UImage* ProgressBar;
	UPROPERTY(EditDefaultsOnly, meta = (bindwidget))
	class UTextBlock* hpText;	
	UPROPERTY()
	class UMaterialInterface* originalMaterial;
	UPROPERTY()
	class UMaterialInstanceDynamic* dynamicMaterial;
};
