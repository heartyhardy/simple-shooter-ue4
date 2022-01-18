// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationOnSight.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

UBTService_PlayerLocationOnSight::UBTService_PlayerLocationOnSight()
{
    NodeName = TEXT("Update Player Location (OnSight)");
}

void UBTService_PlayerLocationOnSight::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(!PlayerPawn || !OwnerComp.GetAIOwner()) return;

    if(OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(
            GetSelectedBlackboardKey(),
            PlayerPawn
        );
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}

