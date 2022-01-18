// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> Crosshairs;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreen;

	UPROPERTY(EditAnywhere, Category = "Game")
	float RestartTime = 3.f;

	UPROPERTY()
	class UUserWidget* HUD;

	FTimerHandle RestartTimer;
};
