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
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

int32 UStatsComponent::TakeDamage(const int32 InDamage, const EAberrationElementType InDamageType)
{
	// Calculate damage
	float DamageMultiplier = GeneralStats.GetMultiplier(EStrategicType::Defense, InDamageType);
	float DamageModifier = (DamageMultiplier - 1.0f) * InDamage;
	int32 Damage = InDamage - DamageModifier;

	// Take damage
	CurrentHealth -= Damage;
	OnTakeDamage.Broadcast();

	// Check if dead
	if(CurrentHealth <= 0)
	{
		OnDeath.Broadcast();
	}

	return Damage;
}

int32 UStatsComponent::DealDamage(const int32 InDamage, const EAberrationElementType InDamageType)
{
	// Calculate damage
	float DamageMultiplier = GeneralStats.GetMultiplier(EStrategicType::Attack, InDamageType);
	int32 Damage = (GeneralStats.Attack + InDamage) * DamageMultiplier;
	
	return Damage;
}