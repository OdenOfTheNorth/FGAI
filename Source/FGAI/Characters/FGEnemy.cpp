#include "FGEnemy.h"

#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "FGAI/AI/Sensing/FGVisionSensingComponent.h"
#include "FGAI/AI/Movement/FGNavMovementComponent.h"
#include "FGAI/AI/Sensing/FGHearingSenseComponent.h"
#include "FGAI/AI/StateMachine/FGStateMachineComponent.h"
#include "FGAI/Components/HealthComponent.h"
#include "FGAI/AI/Sensing/FGTargetingComponent.h"
#include "Kismet/KismetMathLibrary.h"

AFGEnemy::AFGEnemy()
{
	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	// Set size for collision capsule
	Capsule->InitCapsuleSize(55.f, 96.0f);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	Mesh->SetupAttachment(Capsule);
	Mesh->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Mesh->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));

	VisionSensingComponent = CreateDefaultSubobject<UFGVisionSensingComponent>(TEXT("VisionSensing"));
	NavMovementComponent = CreateDefaultSubobject<UFGNavMovementComponent>(TEXT("NavMovementComponent"));
	HearingSensingComponent = CreateDefaultSubobject<UFGHearingSenseComponent>(TEXT("HearingSensing"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	StateMachine = CreateDefaultSubobject<UFGStateMachineComponent>(TEXT("StateMachineComponent"));
	TargetingComponent = CreateDefaultSubobject<UFGTargetingComponent>(TEXT("TargetingComponent"));
}

float AFGEnemy::GetDefaultHalfHeight() const
{
	return Capsule->GetScaledCapsuleHalfHeight();
}



void AFGEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void AFGEnemy::Tick(float DelatTime)
{
	Super::Tick(DelatTime);	
}
