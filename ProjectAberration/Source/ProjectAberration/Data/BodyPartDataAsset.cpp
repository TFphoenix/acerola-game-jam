// Fill out your copyright notice in the Description page of Project Settings.

#include "BodyPartDataAsset.h"

float FPartStats::GetMultiplier(EStrategicType type, EAberrationElementType element)
{
    switch (type)
    {
    case EStrategicType::Attack:
        return AttackMultipliers[element];
    case EStrategicType::Defense:
        return DefenseMultipliers[element];
    default:
        return 0.0f;
    }
}

TMap<EAberrationElementType, float> FPartStats::InitializeModifiers()
{
    TMap<EAberrationElementType, float> map;
    map.Add(EAberrationElementType::Fire, 0.0f);
    map.Add(EAberrationElementType::Water, 0.0f);
    map.Add(EAberrationElementType::Earth, 0.0f);
    map.Add(EAberrationElementType::Air, 0.0f);
    return map;
}