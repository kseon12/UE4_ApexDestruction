// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */

class UTextBlock;

UCLASS()
class TEST_PINGLESTUDIO_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetWaveNumber(int Value);
	void SetScore(int Value);
private:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* WaveNumber;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Score;
};
