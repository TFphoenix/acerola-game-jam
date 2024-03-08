// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPartDataAsset.h"
#include "AberrationSaveData.generated.h"

class UPaperSprite;

USTRUCT(BlueprintType)
struct FRegionProgressData
{
	GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 RegionId = 1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsLocked;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsConquered;
};

USTRUCT(BlueprintType)
struct FAberrationPlayerData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPaperSprite* Avatar;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UBodyPartDataAsset*> AvailableBodyParts;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UBodyPartDataAsset*> CurrentBodyParts;
};