// Fill out your copyright notice in the Description page of Project Settings.

#pragma once



#include "CoreMinimal.h"
#include "frame_rate2.generated.h"

UENUM(BlueprintType)
enum class EFrame_rate2 : uint8
{
    FPS_30 UMETA(DisplayName = "30 FPS"),
    FPS_48 UMETA(DisplayName = "48 FPS"),
    FPS_60 UMETA(DisplayName = "60 FPS"),
    FPS_120 UMETA(DisplayName = "120 FPS"),
    FPS_Uncapped UMETA(DisplayName = "Uncapped"),
    
};

class FFramerateUtils2
{
public:
    
    static int EnumToValue(const EFrame_rate2& InFramerate) 
    {
        switch (InFramerate) 
        {
            case EFrame_rate2::FPS_30: return 30;
            case EFrame_rate2::FPS_48: return 48;
            case EFrame_rate2::FPS_60: return 60;
            case EFrame_rate2::FPS_120: return 120;
            case EFrame_rate2::FPS_Uncapped: return 0;
            default:
                return -1;
        }
    };

    static FString EnumToString(const EFrame_rate2& InFramerate) {
        //switch (InFramerate) {
        //    case EFrame_rate2::FPS_30: return TEXT("30 FPS");
        //    case EFrame_rate2::FPS_48: return TEXT("48 FPS");
        //    case EFrame_rate2::FPS_60: return TEXT("60 FPS");
        //    case EFrame_rate2::FPS_120: return TEXT("120 FPS");
        //    case EFrame_rate2::FPS_Uncapped: return TEXT("Uncapped");
        //    default: return TEXT("Unknown");
        //}
        const auto value = EnumToValue(InFramerate);
        return value > 0
            ? FString::Printf(TEXT("%d FPS"), value)
            : FString::Printf(TEXT("Uncapped"), value);

    }

};

