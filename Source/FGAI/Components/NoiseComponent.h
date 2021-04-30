// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NoiseComponent.generated.h"

class AFGEnemy;
class AFGNoiseActor;
class NoiseActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FGAI_API UNoiseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UNoiseComponent();

	UPROPERTY(EditAnywhere)
	float NoiseRadius = 300;

	void SpawnNoise();

	//void UNoiseComponent::FindAllNoiseActors(UWorld* World, TArray<AFGNoiseActor*>& Out);

	TArray<AFGEnemy*> EnemyArray;
	
	void FindAllEnemys(UWorld* World, TArray<AFGEnemy*>& Out);
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
};
