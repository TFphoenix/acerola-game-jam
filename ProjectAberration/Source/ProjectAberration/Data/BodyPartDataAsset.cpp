// Fill out your copyright notice in the Description page of Project Settings.

#include "BodyPartDataAsset.h"

float FPartStats::GetModifier(EModifierType type, EAberrationElementType element)
{
    try
    {
        switch (type)
        {
        case EModifierType::Attack:
            return AttackModifiers[element];
        case EModifierType::Defense:
            return DefenseModifiers[element];
        }
    }
    catch (...)
    {
    }

    return 0.0f;
}

TMap<EAberrationElementType, float> FPartStats::InitializeModifiers()
{
    TMap<EAberrationElementType, float> map;
    map.Add(EAberrationElementType::Fire, 1.0f);
    map.Add(EAberrationElementType::Water, 1.0f);
    map.Add(EAberrationElementType::Earth, 1.0f);
    map.Add(EAberrationElementType::Air, 1.0f);
    return map;
}