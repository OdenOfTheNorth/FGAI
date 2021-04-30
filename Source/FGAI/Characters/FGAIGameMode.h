// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FGAIGameMode.generated.h"

class AFGNoiseActor;

UCLASS(minimalapi)
class AFGAIGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFGAIGameMode();
	
	TArray<AFGNoiseActor*> FoundActors;
	/*
	void GetAllNoiseActors(UWorld* World, TArray<AFGNoiseActor*>& OutActors);

	void SpawnNoiseActors(FVector SpawnLocation);
	void SpawnNoiseActors(FVector SpawnLocation, float SoundRadius = 350);*/
};


