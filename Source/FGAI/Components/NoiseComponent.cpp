// Fill out your copyright notice in the Description page of Project Settings.


#include "NoiseComponent.h"

#include "EngineUtils.h"
#include "FGAI/FGNoiseActor.h"
#include "FGAI/Characters/FGEnemy.h"

// Sets default values for this component's properties
UNoiseComponent::UNoiseComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UNoiseComponent::BeginPlay()
{
	Super::BeginPlay();
	FindAllEnemys(GetWorld(), EnemyArray);
}
void UNoiseComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);	
}

void UNoiseComponent::SpawnNoise() 
{
	AFGNoiseActor* NoiseActor = GetWorld()->SpawnActor<AFGNoiseActor>(GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
	NoiseActor->Radius = NoiseRadius;
	NoiseActor->NoiseInstigator = GetOwner();
	
	for (AFGEnemy* Enemy : EnemyArray)
	{
		Enemy->HearingSensingComponent->CheakNoise();	//FindAllNoiseActors(GetWorld(), Enemy->HearingSensingComponent->FoundActors);
	}
}

//void UNoiseComponent::FindAllNoiseActors(UWorld* World, TArray<AFGNoiseActor*>& Out)
//{
//	for(TActorIterator<AFGNoiseActor> It(World); It; ++It)
//	{
//		AFGNoiseActor* Actor = *It;
//		Out.Add(Actor);
//	}
//}

void UNoiseComponent::FindAllEnemys(UWorld* World, TArray<AFGEnemy*>& Out)
{
	for(TActorIterator<AFGEnemy> It(World); It; ++It)
	{
		AFGEnemy* Actor = *It;
		Out.Add(Actor);
	}
}

