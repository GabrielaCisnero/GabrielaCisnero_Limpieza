#include "CorruptedCrystal.h"

ACorruptedCrystal::ACorruptedCrystal()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	ContaminationData.ObjectName         = "Cristal Corrupto";
	ContaminationData.ContaminationType  = EContaminationType::Corruption;
	ContaminationData.CleanDuration      = 3.5f;
	ContaminationData.ContaminationColor = FLinearColor(0.5f, 0.0f, 1.0f);
}

void ACorruptedCrystal::BeginPlay()
{
	Super::BeginPlay();
}

FContaminatedObjectData ACorruptedCrystal::GetContaminationData_Implementation() const
{
	return ContaminationData;
}

bool ACorruptedCrystal::CanBeCleaned_Implementation() const
{
	return bActive && !bCleaned;
}

void ACorruptedCrystal::OnCleaningProgress_Implementation(float Progress)
{
	// El cristal se encoge uniformemente mientras se limpia
	float Scale = FMath::Lerp(1.0f, 0.05f, Progress);
	SetActorScale3D(FVector(Scale));
}

void ACorruptedCrystal::OnCleaningCompleted_Implementation()
{
	bActive  = false;
	bCleaned = true;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void ACorruptedCrystal::OnCleaningCancelled_Implementation()
{
	SetActorScale3D(FVector(1.0f));
}