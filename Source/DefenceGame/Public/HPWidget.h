// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HPWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HPWidgetSettings", meta = (BindWidget))
	class UProgressBar* towerHPBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HPWidgetSettings", meta = (BindWidget))
	class UTextBlock* towerHPNum;


	//Tower hp
	float towerMaxHP = 1000.0f;
	//Tower 공격받은 후hp
	float towerCurrentHP = 1000.f;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HPWidgetSettings", meta = (BindWidget))
	//TSubclassOf<class ATower> cTower;


public:

	void OnTakeDamage(int32 attackTowerScore);
	void ShowHealthBar(float hp);
	void SetTowerHP(float hp);
	
};
