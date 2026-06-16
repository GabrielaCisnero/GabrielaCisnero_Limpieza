#include "InfectedDoor.h"

AInfectedDoor::AInfectedDoor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	ContaminationData.ObjectName         = "Puerta Infectada";
	ContaminationData.ContaminationType  = EContaminationType::Infection;
	ContaminationData.CleanDuration      = 5.0f;
	ContaminationData.ContaminationColor = FLinearColor(0.8f, 0.0f, 0.0f);
}

void AInfectedDoor::BeginPlay()
{
	Super::BeginPlay();
}

FContaminatedObjectData AInfectedDoor::GetContaminationData_Implementation() const
{
	return ContaminationData;
}

bool AInfectedDoor::CanBeCleaned_Implementation() const
{
	return bActive && !bCleaned;
}

void AInfectedDoor::OnCleaningProgress_Implementation(float Progress)
{
	// La puerta se oscurece mientras se limpia
	float Scale = FMath::Lerp(1.0f, 0.05f, Progress);
	SetActorScale3D(FVector(1.0f, 1.0f, Scale));
}

void AInfectedDoor::OnCleaningCompleted_Implementation()
{
	bActive  = false;
	bCleaned = true;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AInfectedDoor::OnCleaningCancelled_Implementation()
{
	SetActorScale3D(FVector(1.0f));
}