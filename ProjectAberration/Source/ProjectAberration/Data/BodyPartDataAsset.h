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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	UPaperSprite *Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Ability")
	int32 Damage;
};

USTRUCT(BlueprintType)
struct FPartSprites
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sprites")
	UPaperSprite *Front3Sprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sprites")
	UPaperSprite *Front2Sprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sprites")
	UPaperSprite *Front1Sprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sprites")
	UPaperSprite *BodySprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sprites")
	UPaperSprite *Back1Sprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sprites")
	UPaperSprite *Back2Sprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Sprites")
	UPaperSprite *Back3Sprite;
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
	EMultiplierType ModifierType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	EAberrationElementType AberrationElementType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FPartStats Stats;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FPartAbility> Abilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FPartSprites Sprites;
};
