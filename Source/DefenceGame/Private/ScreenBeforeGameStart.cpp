// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenBeforeGameStart.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void UScreenBeforeGameStart::ShowStartGameText()
{
	startGameText->SetText(FText::FromString(FString(TEXT("Protect\nyour Robo Rumble SafeBox"))));

	startGameText->SetColorAndOpacity(FLinearColor(1, 1, 1, 1));
	
	//PlayAnimation();
	
}

void UScreenBeforeGameStart::ShowStartTextBackground()
{	
	startTextBackground->SetColorAndOpacity(FLinearColor(0.3f, 0.3f, 0.3f, 0.4f));
	
}

