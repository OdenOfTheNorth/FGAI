#include "FGNoiseActor.h"
#include "DrawDebugHelpers.h"

AFGNoiseActor::AFGNoiseActor()
{
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
}

void AFGNoiseActor::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(0.4);	
}

void AFGNoiseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(),Radius, 8, FColor::Green, false, 0 , 6);
}