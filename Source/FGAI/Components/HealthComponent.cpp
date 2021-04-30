// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UHealthComponent::TakeDamage(FHitResult Hit, float Damage, AActor* DamageInstigator)
{
	//Reduce Health
	Health -= Damage;

	if (Health <= 0)
	{
		//ToDo Make the Character died.
	}
	
	//Save Damage Info
	FFGDamageSenseInfo DamageInfo;
	DamageInfo.DamageDirection = (Hit.TraceStart - Hit.ImpactPoint).GetSafeNormal();
	DamageInfo.DamageInstigator = DamageInstigator;
	DamageInfo.DamageImpactLocation = Hit.ImpactPoint;
	OnDamage.Broadcast(DamageInfo);	
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

