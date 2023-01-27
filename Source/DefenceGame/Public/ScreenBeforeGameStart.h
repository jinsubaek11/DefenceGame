// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreenBeforeGameStart.generated.h"

/**
 * 
 */
UCLASS()
class DEFENCEGAME_API UScreenBeforeGameStart : public UUserWidget
{
	GENERATED_BODY()

public:


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ScreenBeforeGameStartSettings", meta = (BindWidget))
	class UTextBlock* startGameText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ScreenBeforeGameStartSettings", meta = (BindWidget))
		class UImage* startTextBackground;
	

public:
	void ShowStartGameText();
	void ShowStartTextBackground();

	
	
};
