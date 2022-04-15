// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Test_PingleStudioHUD.generated.h"

UCLASS()
class ATest_PingleStudioHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATest_PingleStudioHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

