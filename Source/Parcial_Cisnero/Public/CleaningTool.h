#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ContaminationTypes.h"
#include "CleaningTool.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnObjectDetected, AActor*, DetectedActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCleaningProgress, float, Progress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCleaningCompleted);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCleaningCancelled);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PARCIAL_CISNERO_API UCleaningToolComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCleaningToolComponent();

	UPROPERTY(BlueprintAssignable, Category="Cleaning|Events")
	FOnObjectDetected OnObjectDetected;

	UPROPERTY(BlueprintAssignable, Category="Cleaning|Events")
	FOnCleaningProgress OnCleaningProgress;

	UPROPERTY(BlueprintAssignable, Category="Cleaning|Events")
	FOnCleaningCompleted OnCleaningCompleted;

	UPROPERTY(BlueprintAssignable, Category="Cleaning|Events")
	FOnCleaningCancelled OnCleaningCancelled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cleaning|Config")
	float TraceDistance = 150.0f;

	UFUNCTION(BlueprintCallable, Category="Cleaning")
	void StartCleaning();

	UFUNCTION(BlueprintCallable, Category="Cleaning")
	void StopCleaning();

protected:
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

private:
	void PerformLineTrace();
	void UpdateCleaningProgress(float DeltaTime);

	bool  bIsCleaning         = false;
	float CleaningProgress    = 0.0f;
	float CurrentCleanDuration = 3.0f;

	UPROPERTY()
	AActor* CurrentTarget     = nullptr;

	UPROPERTY()
	AActor* ActiveCleanTarget = nullptr;
};