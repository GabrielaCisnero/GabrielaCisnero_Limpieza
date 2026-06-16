#include "CleaningTool.h"
#include "CleanableInterface.h"
#include "CleaningLog.h"
#include "DrawDebugHelpers.h"

UCleaningToolComponent::UCleaningToolComponent()
{
  
    PrimaryComponentTick.bCanEverTick = true;
}

void UCleaningToolComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UCleaningToolComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    PerformLineTrace();

    
    if (bIsCleaning)
    {
        UpdateCleaningProgress(DeltaTime);
    }
}

void UCleaningToolComponent::PerformLineTrace()
{
    AActor* Owner = GetOwner();
    if (!Owner) return;
    
    FVector Start = Owner->GetActorLocation() + FVector(0, 0, 15.0f) + Owner->GetActorForwardVector() * 50.0f;
    
    FVector End   = Start + Owner->GetActorForwardVector() * TraceDistance;

    FHitResult Hit;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(Owner); 

    bool bHit = GetWorld()->LineTraceSingleByChannel(
        Hit, Start, End, ECC_Visibility, Params
    );
    
    DrawDebugLine(GetWorld(), Start, End,
                  bHit ? FColor::Green : FColor::Cyan,
                  false, -1, 0, 2.0f);

    AActor* HitActor = bHit ? Hit.GetActor() : nullptr;
    
    if (HitActor && HitActor->Implements<UCleanableInterface>())
    {
        bool bCanClean = ICleanableInterface::Execute_CanBeCleaned(HitActor);
        
        if (bCanClean && HitActor != CurrentTarget)
        {
            CurrentTarget = HitActor;
            
            OnObjectDetected.Broadcast(HitActor);
        }
    }
    else
    {
        if (CurrentTarget != nullptr)
        {
            CurrentTarget = nullptr;
          
        }
    }
}

void UCleaningToolComponent::StartCleaning()
{
    if (!CurrentTarget) return;
    if (!CurrentTarget->Implements<UCleanableInterface>()) return;
    if (!ICleanableInterface::Execute_CanBeCleaned(CurrentTarget)) return;

    ActiveCleanTarget  = CurrentTarget;
    
    bIsCleaning        = true;
    CleaningProgress   = 0.0f;

    FContaminatedObjectData Data =
        ICleanableInterface::Execute_GetContaminationData(ActiveCleanTarget);
    CurrentCleanDuration = Data.CleanDuration;

    UE_LOG(LogTemp, Log, TEXT("Desinfectando: %s"), *Data.ObjectName);
}

void UCleaningToolComponent::StopCleaning()
{
    if (bIsCleaning && ActiveCleanTarget)
    {
        if (ActiveCleanTarget->Implements<UCleanableInterface>())
        {
            ICleanableInterface::Execute_OnCleaningCancelled(ActiveCleanTarget);
        }
        OnCleaningCancelled.Broadcast();
    }

    bIsCleaning        = false;
    
    CleaningProgress   = 0.0f;
    
    ActiveCleanTarget  = nullptr;
}

void UCleaningToolComponent::UpdateCleaningProgress(float DeltaTime)
{
    if (!ActiveCleanTarget) return;

    CleaningProgress += DeltaTime / CurrentCleanDuration;
    CleaningProgress  = FMath::Clamp(CleaningProgress, 0.0f, 1.0f);

    
    ICleanableInterface::Execute_OnCleaningProgress(ActiveCleanTarget, CleaningProgress);
    OnCleaningProgress.Broadcast(CleaningProgress);

    if (CleaningProgress >= 1.0f)
    {
        ICleanableInterface::Execute_OnCleaningCompleted(ActiveCleanTarget);
        OnCleaningCompleted.Broadcast();

        UCleaningLog* Codex =
            
            GetOwner()->FindComponentByClass<UCleaningLog>();
        if (Codex)
        {
            Codex->RegisterCleaned(ActiveCleanTarget);
        }

        bIsCleaning        = false;
        
        CleaningProgress   = 0.0f;
        ActiveCleanTarget  = nullptr;
    }
}