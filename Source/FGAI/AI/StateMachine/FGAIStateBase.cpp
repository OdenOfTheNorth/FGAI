#include "FGAIStateBase.h"

#include "NavigationSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "FGAI/AI/Movement/FGNavMovementComponent.h"



void UFGAIStateBase::Setup()
{	
	BP_Setup();
}

FName UFGAIStateBase::TickActive(float DeltaTime)
{
	BP_TickActive(DeltaTime);
	
	return PendingStateName;
}

void UFGAIStateBase::OnActivated()
{	
	BP_OnActivated();
}

void UFGAIStateBase::OnDeactivated()
{
	BP_OnDeactivated();
}

void UFGAIStateBase::OnRemoved()
{
	BP_OnRemoved();
}

void UFGAIStateBase::ChangeState(FName NewPendingStateName)
{
	PendingStateName = NewPendingStateName;
}

void UFGAIStateBase::RotateActor()
{
	
}

AActor* UFGAIStateBase::GetOwner() const
{
	return Owner;
}

void UFGAIStateBase::RotateTowardsMovementDirection(const UFGNavMovementComponent* NavMoveComponent)
{
	//FVector Direction = (Owner->GetActorLocation() - MoveLoacation);
	//Direction.IsNormalized();
	
	FVector Velocity = NavMoveComponent->RequestedVelocity;
	if (!Velocity.IsNearlyZero())
	{
		//Velocity.Z = 0.f;
		FRotator Rot = UKismetMathLibrary::MakeRotFromX(Velocity);// MoveLoacation.Rotation();
		OwnerPawn->SetActorRotation(Rot);
	}
}