// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "characterHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UcharacterHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "characterHPSettings", meta = (BindWidget))
	class UProgressBar* charHPBar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "characterHPSettings", meta = (BindWidget))
	class UTextBlock* charHPNum;

	//���� hp�� 1000 
	float charMaxHP = 1000.0f;

	//���ݹ��� ��hp
	float charCurrentHP = 1000.f;

public:

	void ShowHPBar(float hp);
	void SetcharacterHP(float hp);
	void OnTakeDamage(int32 attackTowerScore);
	
};
