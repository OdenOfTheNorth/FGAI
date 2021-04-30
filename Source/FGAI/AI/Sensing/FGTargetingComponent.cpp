#include "FGTargetingComponent.h"
#include "FGVisionSensingComponent.h"
#include "FGHearingSenseComponent.h"
#include "FGAI/Components/HealthComponent.h"
#include "AIController.h"

UFGTargetingComponent::UFGTargetingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;	
}

void UFGTargetingComponent::BeginPlay()
{
	Super::BeginPlay();

	VisionSensingComponent = GetOwner()->FindComponentByClass<UFGVisionSensingComponent>();
	HealthComponent = GetOwner()->FindComponentByClass<UHealthComponent>();
	HearingSensingComponent = GetOwner()->FindComponentByClass<UFGHearingSenseComponent>();
	
	if (VisionSensingComponent != nullptr)
	{
		VisionSensingComponent->OnTargetSensed.AddDynamic(this, &UFGTargetingComponent::Handle_VisionSense);
		VisionSensingComponent->OnTargetLost.AddDynamic(this, &UFGTargetingComponent::Handle_VisionSense);
	}
	
	if (HealthComponent != nullptr)
	{
		HealthComponent->OnDamage.AddDynamic(this, &UFGTargetingComponent::Handle_DamageSense);
	}
	
	if (HearingSensingComponent != nullptr)
	{
		HearingSensingComponent->OnNoiseHeard.AddDynamic(this, &UFGTargetingComponent::Handle_HearingSense);
	}
}

void UFGTargetingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	bNoiseHeard = false;
}

void UFGTargetingComponent::Handle_DamageSense(const FFGDamageSenseInfo& DamageSenseInfo)
{
	
}

void UFGTargetingComponent::Handle_VisionSense(const FFGVisionSensingResults& VisionSenseInfo)
{
	VisionActor = VisionSenseInfo.SensedActor;
	VisionLocation = VisionSenseInfo.SensedActorLocation;
	bSeenPlayer = VisionSenseInfo.ActorInSight;
}

void UFGTargetingComponent::Handle_HearingSense(const FFGHearingInfo& HearingSenseInfo)
{
	NoiseLocation = HearingSenseInfo.NoiseLocation;
	NoiseActor = HearingSenseInfo.NoiseInstigator;
	bNoiseHeard = HearingSenseInfo.bHeardNoise;	
}

inline void UFGTargetingComponent::Move(FVector Location)
{
	AAIController* AIController = Cast<AAIController>(GetOwner()->GetInstigatorController());
	AIController->MoveToLocation(Location);	
}