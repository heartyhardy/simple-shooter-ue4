// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUD = CreateWidget(this, Crosshairs);
    if(HUD)
    {
        HUD->AddToViewport();
    }
}

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUD->RemoveFromViewport();

    if(bIsWinner)
    {
        UUserWidget* WinScreenWidget = CreateWidget(this, WinScreen);
        if(WinScreenWidget)
        {
            WinScreenWidget->AddToViewport();
        }

    }
    else
    {
        UUserWidget* LoseScreenWidget = CreateWidget(this, LoseScreen);
        if(LoseScreenWidget)
        {
            LoseScreenWidget->AddToViewport();
        }
    }

    GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartTime);
}