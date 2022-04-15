// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Test_PingleStudio : ModuleRules
{
	public Test_PingleStudio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "ApexDestruction" });
	}
}
