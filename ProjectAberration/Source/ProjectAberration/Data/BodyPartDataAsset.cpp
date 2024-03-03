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

TMap<EAberrationElementType, float> FPartStats::InitializeMultipliers(const float value)
{
    TMap<EAberrationElementType, float> map;
    map.Add(EAberrationElementType::Fire, value);
    map.Add(EAberrationElementType::Water, value);
    map.Add(EAberrationElementType::Earth, value);
    map.Add(EAberrationElementType::Air, value);
    return map;
}