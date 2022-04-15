// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include <Components/TextBlock.h>

void UHUDWidget::SetWaveNumber(int Value)
{
	WaveNumber->SetText(FText::FromString(FString::Printf(TEXT("%i"), Value)));
}

void UHUDWidget::SetScore(int Value)
{
	Score->SetText(FText::FromString(FString::Printf(TEXT("%i"), Value)));
}


