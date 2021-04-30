#pragma once

#include "CoreMinimal.h"

#include "AIController.h"

#include "FGAIStateBase.generated.h"

class UFGTargetingComponent;
class UFGNavMovementComponent;
class AActor;

UCLASS(BlueprintType, Blueprintable, DefaultToInstanced, EditInlineNew)
class UFGAIStateBase : public UObject
{
	GENERATED_BODY()
public:


	virtual void Setup();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_Setup();

	virtual FName TickActive(float DeltaTime);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_TickActive(float DeltaTime);

	virtual void OnActivated();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnActivated();

	virtual void OnDeactivated();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnDeactivated();

	virtual void OnRemoved();
	UFUNCTION(BlueprintImplementableEvent)
	void BP_OnRemoved();

	UFUNCTION(BlueprintCallable)
	void ChangeState(FName NewPendingStateName);

	UFGNavMovementComponent* MovementComponent;
	void RotateActor();
	
	UPROPERTY(EditAnywhere)
	FName StateName;

	UFUNCTION(BlueprintPure)
	AActor* GetOwner() const;

	UPROPERTY(Transient)
	AActor* Owner = nullptr;

	FName PendingStateName;

	
	void RotateTowardsMovementDirection(const UFGNavMovementComponent* NavMoveComponent);
	
	UFGNavMovementComponent* NavMovementComponent;
	UFGTargetingComponent* TargetingComponent;
	AAIController* Controller;
	APawn* OwnerPawn;
	float WaitTimeRemaining;
	float Wait;
	FVector LastHeardLoacation;
	FVector MoveLoacation;
	bool bPatrolling;
};
