// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ElementDataAsset.h"
#include "BodyPartDataAsset.generated.h"

class UPaperSprite;

UENUM(BlueprintType)
enum class EModifierType : uint8
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
	TMap<EAberrationElementType, float> AttackModifiers = FPartStats::InitializeModifiers();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stats")
	TMap<EAberrationElementType, float> DefenseModifiers = FPartStats::InitializeModifiers();

	float GetModifier(EModifierType type, EAberrationElementType element);
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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EModifierType ModifierType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAberrationElementType AberrationElementType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FPartStats Stats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FPartAbility> Abilities;
};
