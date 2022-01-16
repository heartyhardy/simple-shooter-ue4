// Fill out your copyright notice in the Description page of Project Settings.


#include "KillemAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"


void AKillemAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    if(PlayerController)
    {
        PlayerController->GameHasEnded(nullptr, false);
    }

    for(AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if(!Controller->IsDead()) return;
    }

    EndGame(true);
}

void AKillemAllGameMode::EndGame(bool bPlayerWon)
{
    for(AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bPlayerWon;

        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}