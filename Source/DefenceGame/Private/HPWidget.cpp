// Fill out your copyright notice in the Description page of Project Settings.


#include "HPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UHPWidget::ShowHealthBar(float hp)
{
	//체력바 보여주는 함수
	towerHPBar->SetFillColorAndOpacity(FLinearColor(255, 0, 0, 255));

	towerHPBar->SetPercent(hp);

	towerHPNum->SetText(FText::AsNumber(hp));
	
}

void UHPWidget::GetTowerHP(float attackTowerScore)
{

	//공격당한 후 남은 hp 계산
	towerCurrentHP = towerMaxHP - attackTowerScore;
	UE_LOG(LogTemp, Warning, TEXT("hp of tower is decreasing"))

	if (towerCurrentHP)
	{
		//남은 체력 숫자 보여주기
		ShowHealthBar(towerCurrentHP);
		
	}
}

void UHPWidget::SetTowerHP(float hp)
{
	ShowHealthBar(hp);

}