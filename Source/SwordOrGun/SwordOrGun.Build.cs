// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SwordOrGun : ModuleRules
{
	public SwordOrGun(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { 
			// InitialModules
            "Core", "CoreUObject", "Engine", "InputCore",

            // JsonModules
            "Json", "JsonUtilities" ,

            // Enhanced Input
            "EnhancedInput" ,

            // AI
            "NavigationSystem" ,
            "AIModule",
            "GameplayTasks" 
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
