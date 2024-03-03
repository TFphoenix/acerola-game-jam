// Fill out your copyright notice in the Description page of Project Settings.

#include "StatsComponent.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// Initialize multipliers to 100%
	GeneralStats.AttackMultipliers = FPartStats::InitializeMultipliers(1.0f);
	GeneralStats.DefenseMultipliers = FPartStats::InitializeMultipliers(1.0f);

	bIsDead = false;
}

// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 UStatsComponent::TakeDamage(const int32 &InDamage)
{
	if (bIsDead) return 0;

	// Take damage
	CurrentHealth -= InDamage;
	OnTakeDamage.Broadcast();

	// Check if dead
	if (CurrentHealth <= 0)
	{
		bIsDead = true;
		OnDeath.Broadcast();
	}

	return InDamage;
}

int32 UStatsComponent::CalculateAbilityDamage(const FPartAbility &InAbility, UStatsComponent *InOpponentStats)
{
	if (bIsDead) return 0;

	// Calculate damage dealt
	float DamageMultiplier = GeneralStats.GetMultiplier(EStrategicType::Attack, InAbility.ElementType);
	int32 Damage = (InAbility.Damage + GeneralStats.Attack) * DamageMultiplier;

	// Calculate damage taken
	float OpponentDamageMultiplier = InOpponentStats->GeneralStats.GetMultiplier(EStrategicType::Defense, InAbility.ElementType);
	float OpponentDamageModifier = (OpponentDamageMultiplier - 1.0f) * Damage;
	Damage -= OpponentDamageModifier;

	return Damage;
}