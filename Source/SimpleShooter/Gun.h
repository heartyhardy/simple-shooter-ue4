// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PrimaryFire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, Category = "General")
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, Category = "General")
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class UParticleSystem* MuzzleFlash;

	UPROPERTY(EditAnywhere, Category = "Combat")
	UParticleSystem* BulletImpactParticles;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	float PrimaryAttackDamage = 10.f;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* MuzzleSound;

	UPROPERTY(EditAnywhere, Category ="Combat")
	USoundBase* ImpactSound;

	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	class AController* GetGunController() const;
};
