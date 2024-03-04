// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "BodyPartDataAsset.h"
#include "MapRegionDataAsset.generated.h"

class UPaperSprite;

USTRUCT(BlueprintType)
struct FDynamicStateSprite
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPaperSprite *Default;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPaperSprite *Highlight;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPaperSprite *Pressed;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPaperSprite *Disabled;
};

USTRUCT(BlueprintType)
struct FRegionEnemy
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UBodyPartDataAsset *> AberrationBodyParts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString EnemyName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPaperSprite *EnemyFace;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UBodyPartDataAsset *BodyPartReward;
};

USTRUCT(BlueprintType)
struct FRegionEnvironment
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPaperSprite *EnvironmentBackground;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterial *GroundMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UMaterial *PlatformsMaterial;
};

/**
 *
 */
UCLASS(BlueprintType)
class PROJECTABERRATION_API UMapRegionDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDynamicStateSprite LogoSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDynamicStateSprite DefaultMapSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FDynamicStateSprite ConqueredMapSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FRegionEnemy> Enemies;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FRegionEnvironment Environment;
};
