// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Data/BodyPartDataAsset.h"
#include "StatsComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), BlueprintType)
class PROJECTABERRATION_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

	// Events
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBlueprintOnDeath);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBlueprintOnTakeDamage);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBlueprintOnAttackCritical);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBlueprintOnAttackMissed);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBlueprintOnAttackEvaded);

public:
	// Sets default values for this component's properties
	UStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 TakeDamage(const int32& InDamage);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	int32 CalculateAbilityDamage(const FPartAbility& InAbility, UStatsComponent* InOpponentStats);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPartStats GeneralStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsDead;

	// Events
	UPROPERTY(BlueprintAssignable)
	FBlueprintOnTakeDamage OnTakeDamage;

	UPROPERTY(BlueprintAssignable)
	FBlueprintOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable)
	FBlueprintOnAttackCritical OnAttackCritical;

	UPROPERTY(BlueprintAssignable)
	FBlueprintOnAttackMissed OnAttackMissed;

	UPROPERTY(BlueprintAssignable)
	FBlueprintOnAttackEvaded OnAttackEvaded;
};
