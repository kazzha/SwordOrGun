// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SwordOrGun : ModuleRules
{
	public SwordOrGun(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
