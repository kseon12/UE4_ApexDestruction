// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameplayMode.h"
#include "EnemyCharacter.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Math/UnrealMathUtility.h" 
#include "HUDWidget.h"

ADefaultGameplayMode::ADefaultGameplayMode()
{
	PrimaryActorTick.bCanEverTick = true;	
}

void ADefaultGameplayMode::BeginPlay()
{
	Super::BeginPlay();

	HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), HUDWidgetBlueprint);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport(999);
	}

	auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (Player)
	{
		EnemySpawnLocationCenter = Player->GetActorLocation();
	}
	else
	{
		EnemySpawnLocationCenter = { 350.f, 4.f, 240.f };
	}

	GenerateNewWave();
}

void ADefaultGameplayMode::Tick(float DeltaTime)
{
	if (EnemyLeftToNextWave <= 0)
	{
		//Destroys Enemies withtin spawn radius
		//Important to run it first, since with new wave spawn point will be changed
		DestroyEnemyWithinSpawnRadius();

		auto Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
		if (Player)
		{
			EnemySpawnLocationCenter = Player->GetActorLocation();
		}
		else
		{
			EnemySpawnLocationCenter = { 350.f, 4.f, 240.f };
		}

		EnemyToSpawn += static_cast<int>(EnemyToSpawn * EnemySpawnCountMultiplier);
		EnemySpawnRadius += static_cast<int>(EnemySpawnRadius * EnemySpawnRadiusMultiplier);

		if (UseEnemyRadiusScaleDecrease)
		{
			EnemyRadiusScaleDecrease += EnemyRadiusScaleDecreaseStep;
			if (EnemyRadiusScaleDecrease >= EnemyRadiusScaleMaxDecrease)
			{
				EnemyRadiusScaleDecrease = EnemyRadiusScaleMaxDecrease;
			}
		}

		GenerateNewWave();
	}
}

void ADefaultGameplayMode::GenerateNewWave()
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	FRotator SpawnRotator { 0.0f, 0.0f, 0.0f };

	for (int i = 0; i<EnemyToSpawn; ++i)
	{
		float EnemySpawnOffset = EnemySpawnRadius / 2.f;

		FVector EnemySpawnLocation = {
			FMath::RandRange(EnemySpawnLocationCenter.X - EnemySpawnOffset,EnemySpawnLocationCenter.X + EnemySpawnOffset)
			,FMath::RandRange(EnemySpawnLocationCenter.Y - EnemySpawnOffset,EnemySpawnLocationCenter.Y + EnemySpawnOffset)
			,FMath::RandRange(EnemySpawnLocationCenter.Z,EnemySpawnLocationCenter.Z + EnemySpawnOffset) };
			
		auto SpawnedEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(EnemyToSpawnBlueprint, EnemySpawnLocation, SpawnRotator, SpawnParameters);
		
	}

	EnemyLeftToNextWave = EnemyFragsToNextWave;
	WaveNumber += 1;
	UpdateHUD();
}

void ADefaultGameplayMode::DecrementEnemyLeftToNextWave()
{
	--EnemyLeftToNextWave;
	Score += 1;
	UpdateHUD();
}

void ADefaultGameplayMode::DestroyEnemyWithinSpawnRadius()
{
	TArray<AActor*> EnemyArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(),AEnemyCharacter::StaticClass(), EnemyArray);

	for (auto ActorEnemy : EnemyArray)
	{
		auto Enemy = Cast<AEnemyCharacter>(ActorEnemy);

		FVector EnemyLocation = Enemy->GetActorLocation();

		double Distance = FMath::Sqrt(
			FMath::Square(EnemyLocation.X - EnemySpawnLocationCenter.X)+
			FMath::Square(EnemyLocation.Y - EnemySpawnLocationCenter.Y)+
			FMath::Square(EnemyLocation.Z - EnemySpawnLocationCenter.Z));

		if (Distance <= EnemyWinDestroyRadius)
		{
			if (Enemy->IsActorPendingDestruction())
			{
				continue;
			}

			Enemy->DestroyMesh();
		}
	}
}

void ADefaultGameplayMode::UpdateHUD()
{
	HUDWidget->SetWaveNumber(WaveNumber);
	HUDWidget->SetScore(Score);
}