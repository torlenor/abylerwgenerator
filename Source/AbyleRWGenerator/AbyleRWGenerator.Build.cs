// Some copyright should be here...

using UnrealBuildTool;

public class AbyleRWGenerator : ModuleRules
{
	public AbyleRWGenerator(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });
        PublicDependencyModuleNames.AddRange(new string[] { "ShaderCore", "RenderCore", "RHI", "RuntimeMeshComponent" });

        PrivateIncludePathModuleNames.AddRange(new string[] { "Settings" });
    }
}
