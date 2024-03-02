// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ElementDataAsset.h"
#include "BodyPartDataAsset.generated.h"

class UPaperSprite;

UENUM(BlueprintType)
enum class EMultiplierType : uint8
{
	Attack UMETA(DisplayName = "Attack"),
	Defense UMETA(DisplayName = "Defense")
};

USTRUCT(BlueprintType)
struct FPartStats
{
	GENERATED_USTRUCT_BODY()

	static TMap<EAberrationElementType, float> InitializeModifiers();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stats")
	int32 Health;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stats")
	int32 Attack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stats")
	TMap<EAberrationElementType, float> AttackMultipliers = FPartStats::InitializeModifiers();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stats")
	TMap<EAberrationElementType, float> DefenseMultipliers = FPartStats::InitializeModifiers();

	float GetMultiplier(EMultiplierType type, EAberrationElementType element);
};

USTRUCT(BlueprintType)
struct FPartAbility
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	UPaperSprite *Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	int32 Damage;
};

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTABERRATION_API UBodyPartDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Visuals")
	UPaperSprite *FrontSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Visuals")
	UPaperSprite *BodySprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Visuals")
	UPaperSprite *BackSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	EMultiplierType ModifierType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	EAberrationElementType AberrationElementType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	FPartStats Stats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	TArray<FPartAbility> Abilities;
};
