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
	UFUNCTION(BlueprintCallable, Category = "Health")
	void TakeDamage(const int32 InDamage);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPartStats GeneralStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 CurrentHealth;

	UPROPERTY(BlueprintAssignable)
	FBlueprintOnTakeDamage OnTakeDamage;

	UPROPERTY(BlueprintAssignable)
	FBlueprintOnDeath OnDeath;
};
