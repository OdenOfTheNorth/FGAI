// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "FGAI/AI/Sensing/FGHearingSenseComponent.h"
#include "FGAI/AI/Sensing/FGVisionSensingComponent.h"
#include "FGAI/Components/HealthComponent.h"
#include "FGTargetingComponent.generated.h"


class UFGAIStateBase;
class UFGVisionSensingComponent;
class UFGNavMovementComponent;
class UFGHearingSenseComponent;
class UHealthComponent;

struct FFGDamageSenseInfo;
struct FFGVisionSensingResults;
struct FFGHearingInfo;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FGAI_API UFGTargetingComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	
	UFGTargetingComponent();

	UPROPERTY(VisibleAnywhere)
    UFGVisionSensingComponent* VisionSensingComponent;
	UPROPERTY(VisibleAnywhere)
	UFGNavMovementComponent* NavMovementComponent;
	UPROPERTY(VisibleAnywhere)
	UFGHearingSenseComponent* HearingSensingComponent;
    
    UPROPERTY(VisibleDefaultsOnly, Category = Health)
    UHealthComponent* HealthComponent;

	UFUNCTION(BlueprintCallable)
	void Handle_DamageSense(const FFGDamageSenseInfo& DamageSenseInfo);
	
	UFUNCTION(BlueprintCallable)
	void Handle_VisionSense(const FFGVisionSensingResults& VisionSenseInfo);
	
	UFUNCTION(BlueprintCallable)
	void Handle_HearingSense(const FFGHearingInfo& HearingSenseInfo);

	void Move(FVector Location);


	FFGVisionSensingResults* VisionInfo;
	FFGHearingInfo* HearingInfo;

	//Noise
	AActor* NoiseActor;		
	FVector NoiseLocation;
	bool bNoiseHeard = false;

	//Vision
	AActor* VisionActor;
	FVector VisionLocation;
	bool bSeenPlayer = false;

	//Damage
	AActor* DamageActor;
	FVector DamageLocation;
	bool HasBennDamage = false;
	
	UFGAIStateBase* States;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		//*/
};


