// Fill out your copyright notice in the Description page of Project Settings.

#include "StatsComponent.h"
#include "Math/UnrealMathUtility.h"

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
	if (bIsDead)
		return 0;

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
	if (bIsDead)
		return 0;

	// Evasion
	float EvasionRng = FMath::RandRange(0.0, 1.0);
	if (EvasionRng <= InOpponentStats->GeneralStats.EvasionChance)
	{
		OnAttackEvaded.Broadcast();
		return 0;
	}

	// Hit Chance
	float HitRng = FMath::RandRange(0.0, 1.0);
	if (HitRng < InAbility.HitChance)
	{
		OnAttackMissed.Broadcast();
		return 0;
	}

	// Damage (dealt)
	float DamageMultiplier = GeneralStats.GetMultiplier(EStrategicType::Attack, InAbility.ElementType);
	int32 BaseDamage = InAbility.Damage + GeneralStats.Attack;
	int32 Damage = BaseDamage * DamageMultiplier;

	// Damage (received)
	float OpponentDamageMultiplier = InOpponentStats->GeneralStats.GetMultiplier(EStrategicType::Defense, InAbility.ElementType);
	float OpponentDamageModifier = (OpponentDamageMultiplier - 1.0f) * Damage;
	Damage -= OpponentDamageModifier;

	// Critical Chance
	float CriticalRng = FMath::RandRange(0.0, 1.0);
	if (CriticalRng <= GeneralStats.CriticalChance)
	{
		OnAttackCritical.Broadcast();
		return Damage * 2;
	}

	return Damage;
}