// Fill out your copyright notice in the Description page of Project Settings.


#include "StatsComponent.h"
#include "../Data/ElementDataAsset.h"

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	attackMultipliers[EAberrationElementType::Fire] = 0.0f;
	attackMultipliers[EAberrationElementType::Water] = 0.0f;
	attackMultipliers[EAberrationElementType::Earth] = 0.0f;
	attackMultipliers[EAberrationElementType::Air] = 0.0f;
	defenseMultipliers[EAberrationElementType::Fire] = 0.0f;
	defenseMultipliers[EAberrationElementType::Water] = 0.0f;
	defenseMultipliers[EAberrationElementType::Earth] = 0.0f;
	defenseMultipliers[EAberrationElementType::Air] = 0.0f;
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int UStatsComponent::GetHealth()
{
	return health;
}

int UStatsComponent::GetAttack()
{
	return attack;
}

float UStatsComponent::GetMultiplier(EModifierType type, EAberrationElementType element)
{
	switch(type){
		case EModifierType::Attack:
			return attackMultipliers[element];
		case EModifierType::Defense:
			return defenseMultipliers[element];
	}

	return 0.0f;
}