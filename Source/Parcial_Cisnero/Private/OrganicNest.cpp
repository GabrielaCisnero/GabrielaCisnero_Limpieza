#include "OrganicNest.h"

AOrganicNest::AOrganicNest()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	ContaminationData.ObjectName         = "Nido Organico";
	ContaminationData.ContaminationType  = EContaminationType::Fungus;
	ContaminationData.CleanDuration      = 6.0f;
	ContaminationData.ContaminationColor = FLinearColor(0.3f, 0.6f, 0.0f);
}

void AOrganicNest::BeginPlay()
{
	Super::BeginPlay();
}

FContaminatedObjectData AOrganicNest::GetContaminationData_Implementation() const
{
	return ContaminationData;
}

bool AOrganicNest::CanBeCleaned_Implementation() const
{
	return bActive && !bCleaned;
}

void AOrganicNest::OnCleaningProgress_Implementation(float Progress)
{
	// El nido se achica en todas las direcciones mientras se limpia
	float Scale = FMath::Lerp(1.0f, 0.05f, Progress);
	SetActorScale3D(FVector(Scale));
}

void AOrganicNest::OnCleaningCompleted_Implementation()
{
	bActive  = false;
	bCleaned = true;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AOrganicNest::OnCleaningCancelled_Implementation()
{
	SetActorScale3D(FVector(1.0f));
}