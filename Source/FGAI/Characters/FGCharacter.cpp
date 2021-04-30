#include "FGCharacter.h"

#include "DrawDebugHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "FGAI/Components/FGMovementComponent.h"
#include "FGMovementStatics.h"
#include "FGAI/Components/HealthComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AFGCharacter::AFGCharacter()
{
	PrimaryActorTick.bStartWithTickEnabled = true;

	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	RootComponent = Capsule;
	// Set size for collision capsule
	Capsule->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 2.5f;
	BaseLookUpRate = 2.5f;

	Speed = 1000.0f;
	Gravity = 900.0f;
	IsCrouch = false;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(Capsule);
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh"));
	Mesh->SetOnlyOwnerSee(true);
	Mesh->SetupAttachment(FirstPersonCameraComponent);
	Mesh->bCastDynamicShadow = false;
	Mesh->CastShadow = false;
	Mesh->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	MovementComponent = CreateDefaultSubobject<UFGMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(Capsule);

	NoiseComponent = CreateDefaultSubobject<UNoiseComponent>(TEXT("Noise Component"));
}

void AFGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
		
	FFGFrameMovement FrameMovement = MovementComponent->CreateFrameMovement();
	
	FrameMovement.AddGravity(Gravity * DeltaTime);

	if (!InputVector.IsNearlyZero())
	{
		FVector Forward = FVector::VectorPlaneProject(FirstPersonCameraComponent->GetForwardVector(), FVector::UpVector);
		FVector ForwardMovement = Forward * InputVector.X;
		FVector Right = FirstPersonCameraComponent->GetRightVector() * InputVector.Y;
		FVector Velocity = (ForwardMovement + Right).GetSafeNormal() * Speed * DeltaTime;
		FrameMovement.AddDelta(Velocity);
	}
	
	MovementComponent->Move(FrameMovement);
	spawnTime += DeltaTime;
	if (spawnTime > spawnDelay)
	{
		if(!IsCrouch && MovementComponent->IsMoving)
		{
			NoiseComponent->SpawnNoise();
			spawnTime = 0;
		}
	}	
}

void AFGCharacter::BeginPlay()
{
	Super::BeginPlay();

}

void AFGCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFGCharacter::OnFire);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AFGCharacter::StartCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AFGCharacter::EndCrouch);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AFGCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFGCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	PlayerInputComponent->BindAxis("Turn", this, &AFGCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AFGCharacter::LookUpAtRate);
}

void AFGCharacter::OnFire()
{
	FHitResult Hit;
	FVector Start = FirstPersonCameraComponent->GetComponentLocation();
	//FRotator Direction = FirstPersonCameraComponent->GetComponentLocation().ForwardVector;
	FVector End = Start + FirstPersonCameraComponent->GetComponentRotation().Vector() * 1000;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(GetOwner());
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(), Start, End, TraceType, false, TArray<AActor*>(), EDrawDebugTrace::ForDuration, Hit, true);
	
	if (Hit.bBlockingHit)
	{
		FString output = Hit.Actor->GetName();	
		
		UHealthComponent* Target = Hit.Actor->FindComponentByClass<UHealthComponent>();
		if (Target)
		{
			//UE_LOG(LogTemp, Warning,TEXT("Actor was hit %s"), *output);
			DrawDebugLine(GetWorld(),Start,Hit.GetActor()->GetActorLocation(),FColor::Orange,false,0.5,0,6 );
			Target->TakeDamage(Hit, 10, this);
		}				
	}
}

void AFGCharacter::MoveForward(float Value)
{
	InputVector.X = Value;
}

void AFGCharacter::MoveRight(float Value)
{
	InputVector.Y = Value;
}

void AFGCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate);
}

void AFGCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate);
}

void AFGCharacter::StartCrouch()
{
	UE_LOG(LogTemp, Warning, TEXT("Start Crouch"));
	FVector ScaleVector = FVector(1,1,0.5f);
	Capsule->SetWorldScale3D(ScaleVector);
	IsCrouch = true;
}

void AFGCharacter::EndCrouch()
{
	UE_LOG(LogTemp, Warning, TEXT("End Crouch"));
	FVector ScaleVector = FVector(1,1,1);
	Capsule->SetWorldScale3D(ScaleVector);
	IsCrouch = false;
}
