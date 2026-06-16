#include "CleaningLog.h"
#include "CleanableInterface.h"

void UCleaningLog::RegisterCleaned(AActor* CleanedActor)
{
	if (!CleanedActor) return;
	if (!CleanedActor->Implements<UCleanableInterface>()) return;

	FContaminatedObjectData Data =
		ICleanableInterface::Execute_GetContaminationData(CleanedActor);

	FCleaningLogEntry Entry;
	Entry.ObjectName = Data.ObjectName;
	Entry.Type       = Data.ContaminationType;
	Entry.CleanedAt  = FDateTime::Now().ToString();

	Entries.Add(Entry);

	UE_LOG(LogTemp, Log, TEXT("[LOG] Limpiado: %s | Total limpiados: %d"),
		   *Entry.ObjectName, Entries.Num());
	float Progress = (float)Entries.Num() / (float)TotalObjects;
	OnWorldProgressUpdated.Broadcast(Progress);
}