#include "FGHearingSenseComponent.h"


#include "DrawDebugHelpers.h"
#include "FGAI/FGNoiseActor.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"

UFGHearingSenseComponent::UFGHearingSenseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UFGHearingSenseComponent::CheakNoise()
{
	//Todo fixed only cheak for noise when it's spwaned
	
	FindAllNoiseActor(GetWorld(),FoundActors);

	UE_LOG(LogTemp,Warning,TEXT("CheakNoise"));
	
	FVector MyLocation = GetOwner()->GetActorLocation();
	float MyRadiusSq = FMath::Square(HearingRange);
	
	for (AFGNoiseActor* NoiseActor : FoundActors)
	{
		if (NoiseActor != nullptr) 
		{
			float DistanceToNoiseSq = MyLocation.DistSquared(NoiseActor->GetActorLocation(), MyLocation);
			float NoiseRangeSq = FMath::Square(NoiseActor->Radius);
			float NoiseRadiuses = NoiseRangeSq + MyRadiusSq;

			if (DistanceToNoiseSq < NoiseRadiuses)
			{				
				HearingInfo.NoiseInstigator = NoiseActor->NoiseInstigator;
				HearingInfo.NoiseLocation = NoiseActor->GetActorLocation();
				HearingInfo.Range = NoiseActor->Radius;
				HearingInfo.bHeardNoise = true;
				OnNoiseHeard.Broadcast(HearingInfo);
				UE_LOG(LogTemp, Warning, TEXT("Noise Heard"));
			}
		}
	}	
	FoundActors.Empty();
}

void UFGHearingSenseComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UFGHearingSenseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{	
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(),HearingRange, 16, FColor::Red, false, 0 , 6);
}
 

void UFGHearingSenseComponent::FindAllNoiseActor(UWorld* World, TArray<AFGNoiseActor*>& Out)
{
	for (TActorIterator<AFGNoiseActor> It(World); It; ++It)
	{
		Out.Add(*It);
	}
}

