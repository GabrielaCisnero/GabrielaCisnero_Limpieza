// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Parcial_Cisnero : ModuleRules
{
	public Parcial_Cisnero(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Parcial_Cisnero",
			"Parcial_Cisnero/Variant_Platforming",
			"Parcial_Cisnero/Variant_Platforming/Animation",
			"Parcial_Cisnero/Variant_Combat",
			"Parcial_Cisnero/Variant_Combat/AI",
			"Parcial_Cisnero/Variant_Combat/Animation",
			"Parcial_Cisnero/Variant_Combat/Gameplay",
			"Parcial_Cisnero/Variant_Combat/Interfaces",
			"Parcial_Cisnero/Variant_Combat/UI",
			"Parcial_Cisnero/Variant_SideScrolling",
			"Parcial_Cisnero/Variant_SideScrolling/AI",
			"Parcial_Cisnero/Variant_SideScrolling/Gameplay",
			"Parcial_Cisnero/Variant_SideScrolling/Interfaces",
			"Parcial_Cisnero/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
