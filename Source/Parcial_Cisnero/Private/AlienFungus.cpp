#include "AlienFungus.h"

AAlienFungus::AAlienFungus()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	ContaminationData.ObjectName        = "Alien Fungus";
	ContaminationData.ContaminationType = EContaminationType::Fungus;
	ContaminationData.CleanDuration     = 4.0f;
	ContaminationData.ContaminationColor = FLinearColor(0.1f, 0.9f, 0.1f);
}

void AAlienFungus::BeginPlay()
{
	Super::BeginPlay();
}

FContaminatedObjectData AAlienFungus::GetContaminationData_Implementation() const
{
	return ContaminationData;
}

bool AAlienFungus::CanBeCleaned_Implementation() const
{
	return bActive && !bCleaned;
}

void AAlienFungus::OnCleaningProgress_Implementation(float Progress)
{
	float Scale = FMath::Lerp(1.0f, 0.05f, Progress);
	SetActorScale3D(FVector(Scale));
}

void AAlienFungus::OnCleaningCompleted_Implementation()
{
	bActive  = false;
	bCleaned = true;
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AAlienFungus::OnCleaningCancelled_Implementation()
{
	SetActorScale3D(FVector(1.0f));
}