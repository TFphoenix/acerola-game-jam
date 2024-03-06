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
	UPaperSprite *Background;

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
	// Data
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	int32 ID;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	TArray<FRegionEnemy> Enemies;

	// State
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	bool bIsLocked = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="State")
	bool bIsConquered = false;

	// Visuals
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Visuals")
	FDynamicStateSprite LogoSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Visuals")
	FDynamicStateSprite DefaultMapSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Visuals")
	FDynamicStateSprite ConqueredMapSprite;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Visuals")
	FRegionEnvironment Environment;

public:
	UFUNCTION(BlueprintCallable, Category="Visuals")
	UPaperSprite* GetLogoSprite();

	UFUNCTION(BlueprintCallable, Category="Visuals")
	UPaperSprite* GetMapSprite(bool InHighlight);
};
