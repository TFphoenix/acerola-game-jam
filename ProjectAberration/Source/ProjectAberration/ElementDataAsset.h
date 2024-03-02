// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "ElementDataAsset.generated.h"


UENUM(BlueprintType)
enum class EAberrationElementType : uint8
{
	Fire UMETA(DisplayName = "Fire"),
	Water UMETA(DisplayName = "Water"),
	Earth UMETA(DisplayName = "Earth"),
	Air UMETA(DisplayName = "Air")
};

USTRUCT(BlueprintType)
struct FAberrationElementData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor ElementColour = FLinearColor::White;
};

/**
 *
 */
UCLASS(BlueprintType)
class PROJECTABERRATION_API UElementDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<EAberrationElementType, FAberrationElementData> Elements;
};
