#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ContaminationTypes.h"
#include "CleanableInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class UCleanableInterface : public UInterface
{
	GENERATED_BODY()
};

class PARCIAL_CISNERO_API ICleanableInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FContaminatedObjectData GetContaminationData() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnCleaningProgress(float Progress);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnCleaningCompleted();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnCleaningCancelled();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool CanBeCleaned() const;
};