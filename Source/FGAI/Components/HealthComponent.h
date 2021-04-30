#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

USTRUCT(BlueprintType)
struct FFGDamageSenseInfo
{
	GENERATED_BODY()
public:
	UPROPERTY()
	AActor* DamageInstigator;
	UPROPERTY()
	FVector DamageDirection;
	UPROPERTY()
	FVector DamageImpactLocation;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FFGDamageSenseDelegate, const FFGDamageSenseInfo&, Results);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FGAI_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();
	void TakeDamage(FHitResult Hit, float Damage, AActor* DamageInstigator);

	UPROPERTY(VisibleAnywhere)
	float Health = 100;

	FFGDamageSenseDelegate OnDamage;
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		
};
