// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ElementDataAsset.h"
#include "StatsComponent.generated.h"


UENUM(BlueprintType)
enum class EModifierType : uint8
{
	Attack UMETA(DisplayName = "Attack"),
	Defense UMETA(DisplayName = "Defense")
};

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJECTABERRATION_API UStatsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

private:
	int health = 0;
	int attack = 0;
	TMap<EAberrationElementType, float> attackMultipliers;
	TMap<EAberrationElementType, float> defenseMultipliers;

public:
	int GetHealth();
	int GetAttack();
	float GetMultiplier(EModifierType type, EAberrationElementType element);
};
