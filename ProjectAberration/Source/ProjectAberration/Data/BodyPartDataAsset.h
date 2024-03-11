// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ElementDataAsset.h"
#include "BodyPartDataAsset.generated.h"

class UPaperSprite;

UENUM(BlueprintType)
enum class EStrategicType : uint8
{
	Attack UMETA(DisplayName = "Attack"),
	Defense UMETA(DisplayName = "Defense")
};

USTRUCT(BlueprintType)
struct FPartStats
{
	GENERATED_USTRUCT_BODY()

	static TMap<EAberrationElementType, float> InitializeMultipliers(const float value = 0.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	int32 Attack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	TMap<EAberrationElementType, float> AttackMultipliers = FPartStats::InitializeMultipliers();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	TMap<EAberrationElementType, float> DefenseMultipliers = FPartStats::InitializeMultipliers();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float CriticalChance = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Stats")
	float EvasionChance = 0.0f;

	float GetMultiplier(EStrategicType type, EAberrationElementType element);
};

USTRUCT(BlueprintType)
struct FPartAbility
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	UPaperSprite *Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	int32 Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	float HitChance = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	float SpecialEffectChance = 0.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	EAberrationElementType ElementType;
};

USTRUCT(BlueprintType)
struct FPartSprites
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sprites")
	UPaperSprite *FrontSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sprites")
	UPaperSprite *BodySprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sprites")
	UPaperSprite *BackSprite;
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
	bool bIsBody;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 BodySlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EStrategicType StrategicType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAberrationElementType ElementType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FPartStats Stats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FPartAbility> Abilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FPartSprites Sprites;
};
