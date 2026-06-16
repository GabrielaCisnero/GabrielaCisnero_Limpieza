#pragma once
#include "CoreMinimal.h"
#include "ContaminationTypes.generated.h"

UENUM(BlueprintType)
enum class EContaminationType : uint8
{
	Acid        UMETA(DisplayName = "Acido"),
	Fungus      UMETA(DisplayName = "Hongo"),
	Infection   UMETA(DisplayName = "Infeccion"),
	Corruption  UMETA(DisplayName = "Corrupcion")
};

USTRUCT(BlueprintType)
struct FContaminatedObjectData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ObjectName = "Objeto Contaminado";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EContaminationType ContaminationType = EContaminationType::Fungus;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CleanDuration = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FLinearColor ContaminationColor = FLinearColor::Green;
};