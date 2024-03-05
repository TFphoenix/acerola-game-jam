// Fill out your copyright notice in the Description page of Project Settings.

#include "MapRegionDataAsset.h"

UPaperSprite *UMapRegionDataAsset::GetLogoSprite()
{
    if (bIsLocked)
    {
        return LogoSprite.Disabled;
    }
    else
    {
        return LogoSprite.Default;
    }
}

UPaperSprite *UMapRegionDataAsset::GetMapSprite(bool InHighlight = false)
{
    if (bIsLocked)
    {
        return DefaultMapSprite.Disabled;
    }
    else
    {
        if (bIsConquered)
        {
            return InHighlight ? ConqueredMapSprite.Highlight : ConqueredMapSprite.Default;
        }
        else
        {
            return InHighlight ? DefaultMapSprite.Highlight : DefaultMapSprite.Default;
        }
    }
}