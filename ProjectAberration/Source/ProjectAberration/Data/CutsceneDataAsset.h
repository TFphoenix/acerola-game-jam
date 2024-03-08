// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CutsceneDataAsset.generated.h"

class UPaperSprite;

USTRUCT(BlueprintType)
struct FScenePerson
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPaperSprite *Avatar;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FColor Color;
};

USTRUCT(BlueprintType)
struct FSceneData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPaperSprite *Background;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 DialogPerson;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString DialogText;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UPaperSprite *Item;
};

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTABERRATION_API UCutsceneDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Cutscene")
	FScenePerson Person1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Cutscene")
	FScenePerson Person2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Cutscene")
	TArray<FSceneData> Scenes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Functionality")
	FName NextLevel;
};
