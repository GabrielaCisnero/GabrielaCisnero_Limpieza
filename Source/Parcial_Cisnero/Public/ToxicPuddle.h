#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CleanableInterface.h"
#include "ToxicPuddle.generated.h"

UCLASS()
class PARCIAL_CISNERO_API AToxicPuddle : public AActor, public ICleanableInterface
{
	GENERATED_BODY()

public:
	AToxicPuddle();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Contamination")
	FContaminatedObjectData ContaminationData;

	virtual FContaminatedObjectData GetContaminationData_Implementation() const override;
	virtual bool CanBeCleaned_Implementation() const override;
	virtual void OnCleaningProgress_Implementation(float Progress) override;
	virtual void OnCleaningCompleted_Implementation() override;
	virtual void OnCleaningCancelled_Implementation() override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

private:
	bool bActive  = true;
	bool bCleaned = false;
};