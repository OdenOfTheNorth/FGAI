// Fill out your copyright notice in the Description page of Project Settings.


#include "FGAIState.h"

#include "NavigationSystem.h"
#include "FGAI/AI/Movement/FGNavMovementComponent.h"
#include "FGAI/AI/Sensing/FGTargetingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "NavigationSystem.h"

//--------------------------------------------------------------------------------------------------------------------//
//	Idle
//--------------------------------------------------------------------------------------------------------------------//

void UUFG_AI_Idle::Setup()
{
	TargetingComponent = GetOwner()->FindComponentByClass<UFGTargetingComponent>();
	MovementComponent = GetOwner()->FindComponentByClass<UFGNavMovementComponent>();
	WaitTimeRemaining = Wait;
	StateName = "UUFG_AI_Idle";
	
}

FName UUFG_AI_Idle::TickActive(float DeltaTime)
{
	//TODO Make This not ugly, sleep on it.
	UE_LOG(LogTemp,Warning,TEXT("UUFG_AI_Idle"));
	RotateTowardsMovementDirection(MovementComponent);
	if (TargetingComponent->bNoiseHeard) 
	{
		LastHeardLoacation = TargetingComponent->NoiseLocation;
		TargetingComponent->Move(LastHeardLoacation);
		//ChangeState("UFG_AI_Suspicious");
	}

	if (TargetingComponent->bSeenPlayer) 
	{
		if (Controller != nullptr)
		{
			Controller->MoveToLocation(TargetingComponent->VisionLocation);
			//ChangeState("UFG_AI_Attacking");
		}
	}
	
	return PendingStateName;
}

void UUFG_AI_Idle::OnActivated()
{
	WaitTimeRemaining = Wait;
}

void UUFG_AI_Idle::OnDeactivated()
{
	PendingStateName = NAME_None;
}

void UUFG_AI_Idle::RotateTowardsMovementDirection(const UFGNavMovementComponent* NavMoveComponent)
{
}

//--------------------------------------------------------------------------------------------------------------------//
//	Suspicious
//--------------------------------------------------------------------------------------------------------------------//

void UFG_AI_Suspicious::Setup()
{
	TargetingComponent = GetOwner()->FindComponentByClass<UFGTargetingComponent>();
	NavMovementComponent = GetOwner()->FindComponentByClass<UFGNavMovementComponent>();
	WaitTimeRemaining = 10;
	StateName = "UFG_AI_Suspicious";
	
}

FName UFG_AI_Suspicious::TickActive(float DeltaTime)
{
	//TODO Make This not ugly, sleep on it.
	UE_LOG(LogTemp,Warning,TEXT("UFG_AI_Suspicious"));
	RotateTowardsMovementDirection(MovementComponent);
	WaitTimeRemaining -= DeltaTime;
	if (WaitTimeRemaining < 0)
	{
		//ChangeState("UFG_AI_Patrolling");
		WaitTimeRemaining = Wait;
	}
	
	if (TargetingComponent->bSeenPlayer) 
	{	
		TargetingComponent->Move(TargetingComponent->VisionActor->GetActorLocation());
		//ChangeState("UFG_AI_Attacking");
	}

	if (TargetingComponent->bNoiseHeard) 
	{
		LastHeardLoacation = TargetingComponent->NoiseLocation;
		TargetingComponent->Move(LastHeardLoacation);
		bPatrolling = false;
		//ChangeState("UFG_AI_Suspicious");
	}
	
	return PendingStateName;
}

void UFG_AI_Suspicious::OnActivated()
{	
	if (!NavMovementComponent->IsMoving())
	{
		//ChangeState("UUFG_AI_Idle");
	}
}

//--------------------------------------------------------------------------------------------------------------------//
//	UFG_AI_Patrolling
//--------------------------------------------------------------------------------------------------------------------//

void UFG_AI_Patrolling::Setup()
{
	OwnerPawn = Cast<APawn>(Owner);	
	TargetingComponent = GetOwner()->FindComponentByClass<UFGTargetingComponent>();
	MovementComponent = GetOwner()->FindComponentByClass<UFGNavMovementComponent>();
	WaitTimeRemaining = Wait;
	StateName = "UFG_AI_Patrolling";
	bPatrolling = true;
}

FName UFG_AI_Patrolling::TickActive(float DeltaTime)
{
	//TODO Make This not ugly, sleep on it.
	UE_LOG(LogTemp,Warning,TEXT("UFG_AI_Patrolling"));
	Super::TickActive(DeltaTime);
	RotateTowardsMovementDirection(MovementComponent);
	WaitTimeRemaining -= DeltaTime;
	
	if(WaitTimeRemaining < 0 && bPatrolling)
	{
		SetNextLocation();
		WaitTimeRemaining = Wait;
	}//else if (WaitTimeRemaining < 0 ){	//bPatrolling = true;	}

	if (TargetingComponent->bNoiseHeard)
	{
		LastHeardLoacation = TargetingComponent->NoiseLocation;
		TargetingComponent->Move(LastHeardLoacation);
		//bPatrolling = false;
		//ChangeState("UFG_AI_Suspicious");
	}
	
	if (TargetingComponent->bSeenPlayer)
	{	
		LastHeardLoacation = TargetingComponent->VisionActor->GetActorLocation();
		TargetingComponent->Move(LastHeardLoacation);
		UE_LOG(LogTemp, Warning, TEXT("SeenPlayer"));
		//bPatrolling = false;
		//ChangeState("UFG_AI_Attacking");
	}

	if (OwnerPawn->GetActorLocation() == LastHeardLoacation)
	{
		bPatrolling = true;
		WaitTimeRemaining = Wait;
		TargetingComponent->bNoiseHeard = false;
	}
	
	return PendingStateName;
}

void UFG_AI_Patrolling::OnActivated()
{
	
}

void UFG_AI_Patrolling::SetNextLocation()
{
	FVector RandomPoint;
	UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, OwnerPawn->GetActorLocation(), RandomPoint, 2000.f);
	TargetingComponent->Move(RandomPoint);
}

//--------------------------------------------------------------------------------------------------------------------//
// UFG_AI_Attacking
//--------------------------------------------------------------------------------------------------------------------//

void UFG_AI_Attacking::Setup()
{
	StateName = "UFG_AI_Attacking";
	
}

FName UFG_AI_Attacking::TickActive(float DeltaTime)
{
	UE_LOG(LogTemp,Warning,TEXT("UFG_AI_Attacking"));
	//ChangeState("UFG_AI_Suspicious");
	
	RotateTowardsMovementDirection(MovementComponent);
	return PendingStateName;
}

void UFG_AI_Attacking::OnActivated()
{
	
}

void UFG_AI_Attacking::SetNextLocation()
{
	
}



