#pragma once

#include "FGAI/AI/Sensing/FGTargetingComponent.h"
#include "GameFramework/Pawn.h"
#include "FGEnemy.generated.h"

class USkeletalMeshComponent;
class UCapsuleComponent;
class UCameraComponent;
class UFGVisionSensingComponent;
class UFGNavMovementComponent;
class UFGHearingSenseComponent;
class UHealthComponent;
class UFGStateMachineComponent;

UCLASS()
class AFGEnemy : public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleDefaultsOnly, Category=Collision)
	UCapsuleComponent* Capsule;

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, Category = Vision)
	UFGVisionSensingComponent* VisionSensingComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Movement)
	UFGNavMovementComponent* NavMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Hearing)
	UFGHearingSenseComponent* HearingSensingComponent;
	
	UPROPERTY(VisibleDefaultsOnly, Category = Health)
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = State)
	UFGStateMachineComponent* StateMachine;

	UPROPERTY(VisibleDefaultsOnly, Category = Senses)
	UFGTargetingComponent* TargetingComponent;

	AFGEnemy();

	virtual float GetDefaultHalfHeight() const override;

	virtual void Tick(float DeltaTime) override;

	FVector PositionToMoveToVector;
	
protected:
	virtual void BeginPlay();

	UCapsuleComponent* GetCapsule() const { return Capsule; }

	bool ActorSeen = false;
	AActor* Player;
};

