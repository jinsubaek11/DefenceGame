// Fill out your copyright notice in the Description page of Project Settings.


#include "HPWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UHPWidget::ShowHealthBar(float hp)
{
	if(!towerHPBar) return;

	towerHPBar->SetPercent(hp / towerMaxHP);
	towerHPNum->SetText(FText::AsNumber(hp));
	
}

void UHPWidget::OnTakeDamage(int32 attackTowerScore)
{

	//���ݴ��� �� ���� hp ���
	towerCurrentHP = towerMaxHP - attackTowerScore;
	UE_LOG(LogTemp, Warning, TEXT("hp of tower is decreasing"))

	if (towerCurrentHP)
	{
		//���� ü�� ���� �����ֱ�
		ShowHealthBar(towerCurrentHP);
		
	}
}

void UHPWidget::SetTowerHP(float hp)
{
	ShowHealthBar(hp);
}