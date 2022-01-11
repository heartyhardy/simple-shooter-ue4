// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"


void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    
    if(AIBehavior)
    {
        RunBehaviorTree(AIBehavior);

        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

        if(!PlayerPawn) return;
        GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());
        
        if(!GetPawn()) return;
        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
    }
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);



}

// This isn't needed anymore because we are using behavior trees
// APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

// if(LineOfSightTo(PlayerPawn))
// {
//     SetFocus(PlayerPawn);
//     MoveToActor(PlayerPawn, AcceptanceRadius);
// }
// else
// {
//     ClearFocus(EAIFocusPriority::Gameplay);
//     StopMovement();
// }