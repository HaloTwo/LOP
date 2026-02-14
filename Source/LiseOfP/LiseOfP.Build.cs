// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class LiseOfP : ModuleRules
{
    public LiseOfP(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "EnhancedInput",
            "GameplayAbilities",
            "GameplayTags",
            "GameplayTasks",
            "AIModule",
            "AnimGraphRuntime",
            "MotionWarping",
            "UMG",
            "LevelSequence", 
            "MovieScene",
            "Niagara",
            "PhysicsCore",
        });

        PrivateDependencyModuleNames.AddRange(new string[] { });
    }
}
