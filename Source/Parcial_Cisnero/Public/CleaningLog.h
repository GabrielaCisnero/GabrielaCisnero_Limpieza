#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ContaminationTypes.h"
#include "CleaningLog.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWorldProgressUpdated, float, WorldProgress);

USTRUCT(BlueprintType)
struct FCleaningLogEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FString ObjectName;

	UPROPERTY(BlueprintReadOnly)
	EContaminationType Type;

	UPROPERTY(BlueprintReadOnly)
	FString CleanedAt;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PARCIAL_CISNERO_API UCleaningLog : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable, Category="Cleaning|Events")
	FOnWorldProgressUpdated OnWorldProgressUpdated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Cleaning")
	int32 TotalObjects = 5;

	UFUNCTION(BlueprintCallable)
	void RegisterCleaned(AActor* CleanedActor);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FCleaningLogEntry> GetAllEntries() const { return Entries; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	int32 GetCleanedCount() const { return Entries.Num(); }

private:
	TArray<FCleaningLogEntry> Entries;
};