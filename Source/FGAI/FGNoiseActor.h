// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGNoiseActor.generated.h"

class USceneComponent;

UCLASS()
class FGAI_API AFGNoiseActor : public AActor
{
	GENERATED_BODY()	
public:	
	// Sets default values for this actor's properties
	AFGNoiseActor();
	UPROPERTY()
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere)
	float Radius = 350.f;

	AActor* NoiseInstigator;

	//UFUNCTION()
	//void SpawnNoise(FVector Location, AActor* NoiseInstigator);
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};


