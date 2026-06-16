#include "ToxicPuddle.h"

AToxicPuddle::AToxicPuddle()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	ContaminationData.ObjectName         = "Charco Toxico";
	ContaminationData.ContaminationType  = EContaminationType::Acid;
	ContaminationData.CleanDuration      = 2.5f;
	ContaminationData.ContaminationColor = FLinearColor(0.8f, 1.0f, 0.0f);
}

void AToxicPuddle::BeginPlay()
{
	Super::BeginPlay();
}

FContaminatedObjectData AToxicPuddle::GetContaminationData_Implementation() const
{
	return ContaminationData;
}

bool AToxicPuddle::CanBeCleaned_Implementation() const
{
	return bActive && !bCleaned;
}

void AToxicPuddle::OnCleaningProgress_Implementation(float Progress)
{
	// El charco se achica mientras se limpia
	float Scale = FMath::Lerp(1.0f, 0.0f, Progress);
	SetActorScale3D(FVector(Scale, Scale, 1.0f));
}

void AToxicPuddle::OnCleaningCompleted_Implementation()
{
	bActive  = false;
	bCleaned = true;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AToxicPuddle::OnCleaningCancelled_Implementation()
{
	SetActorScale3D(FVector(1.0f));
}