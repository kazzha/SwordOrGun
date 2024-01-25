
using UnrealBuildTool;

public class SwordOrGunSettings : ModuleRules
{
    public SwordOrGunSettings(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            // Initial Modules
            "Core", "CoreUObject", "Engine", "InputCore",
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}