#include "FGAIGameMode.h"
#include "EngineUtils.h"
#include "FGAI/FGNoiseActor.h"

AFGAIGameMode::AFGAIGameMode()	: Super()
{
}
/*
void AFGAIGameMode::GetAllNoiseActors(UWorld* World, TArray<AFGNoiseActor*>& OutActors)
{
	for(TActorIterator<AFGNoiseActor> It(World); It; ++It)
	{
		AFGNoiseActor* Actor = *It;
		OutActors.Add(Actor);
	}
}

void AFGAIGameMode::SpawnNoiseActors(FVector SpawnLocation)
{
	auto* NoiseActor = GetWorld()->SpawnActor<AFGNoiseActor>(GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
	GetAllNoiseActors(GetWorld(),FoundActors);
}

void AFGAIGameMode::SpawnNoiseActors(FVector SpawnLocation, float SoundRadius)
{
	auto* NoiseActor = GetWorld()->SpawnActor<AFGNoiseActor>(GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
	NoiseActor->Radius = SoundRadius;
	GetAllNoiseActors(GetWorld(),FoundActors);
}*/



