// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DefaultGameplayMode.generated.h"

/**
 * 
 */
class AEnemyCharacter;
class UHUDWidget;

UCLASS()
class TEST_PINGLESTUDIO_API ADefaultGameplayMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ADefaultGameplayMode();

	virtual void Tick(float DeltaTime) override;
protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Prefference")
	TSubclassOf<AEnemyCharacter> EnemyToSpawnBlueprint;

	UPROPERTY(EditAnywhere, Category = "Prefference", meta = (ClampMin = 15))
	int EnemyToSpawn = 15;

	UPROPERTY(EditAnywhere, Category = "Prefference", meta = (ClampMin = 10))
	int EnemyFragsToNextWave = 10;

	UPROPERTY(EditAnywhere, Category = "Prefference", meta = (ClampMin = 1500))
	int EnemySpawnRadius = 2000;

	UPROPERTY(EditAnywhere, Category = "Prefference", meta = (ClampMin = 0))
	int EnemyWinDestroyRadius = 1500;

	UPROPERTY(EditAnywhere, Category = "Prefference", meta = (ClampMin = 0.1f))
	float EnemySpawnCountMultiplier = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Prefference", meta = (ClampMin = 0.05f))
	float EnemySpawnRadiusMultiplier = 0.05f;

	UPROPERTY(EditAnywhere, Category = "Prefference", meta = (ClampMin = 0.1f))
	float EnemyToEnemySpawnDistance = 80.0f;

	UPROPERTY(EditAnywhere, Category = "Prefference")
	bool UseEnemyRadiusScaleDecrease = true;

	UPROPERTY(EditAnywhere, Category = "Prefference", meta = (ClampMin = 0.01f, ClampMax = 0.1f))
	float EnemyRadiusScaleDecreaseStep = 0.05f;

	UPROPERTY(EditAnywhere, Category = "Prefference", meta = (ClampMin = 0.1f, ClampMax = 0.5f))
	float EnemyRadiusScaleMaxDecrease = 0.5f;

	UPROPERTY(EditAnywhere, Category = "Prefference")
	TSubclassOf<UHUDWidget> HUDWidgetBlueprint;

	FVector EnemySpawnLocationCenter;

	int EnemyLeftToNextWave = 0;

	float EnemyRadiusScaleDecrease = 0.0f;

	bool isFirstWave = true;

	UHUDWidget* HUDWidget;

	int Score = 0;

	int WaveNumber = 0;

	void GenerateNewWave();

	void DestroyEnemyWithinSpawnRadius();

	void UpdateHUD();

public:

	void DecrementEnemyLeftToNextWave();

	float GetEnemyToEnemySpawnDistance()
	{
		return EnemyToEnemySpawnDistance;
	};

	float GetEnemyRadiusScaleDecrease()
	{
		return EnemyRadiusScaleDecrease;
	}
};
