// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

#define out

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PrimaryFire()
{
	UGameplayStatics::SpawnEmitterAttached(
		MuzzleFlash,
		Mesh,
		TEXT("MuzzleFlashSocket")
	);

	APawn* GunOwner = Cast<APawn>(GetOwner());
	if(!GunOwner) return;

	AController* GunOwnerController = GunOwner->GetController();
	if(!GunOwnerController) return;

	FVector Location;
	FRotator Rotation;

	GunOwnerController->GetPlayerViewPoint(out Location, out Rotation);

	FVector GunMaxRange = Location + Rotation.Vector() * MaxRange;

	FHitResult HitResult;

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Location,
		GunMaxRange,
		ECollisionChannel::ECC_GameTraceChannel1
	);

	if(bHit && BulletImpactParticles)
	{
		FVector BulletHitDirection = -Rotation.Vector();

		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			BulletImpactParticles,
			HitResult.Location,
			BulletHitDirection.Rotation()
		);


		AActor* ActorGotHit = HitResult.GetActor();

		if(ActorGotHit)
		{
			FPointDamageEvent PrimaryAttackDamageEvent(PrimaryAttackDamage, HitResult, BulletHitDirection, nullptr);
			
			ActorGotHit->TakeDamage(
				PrimaryAttackDamage, 
				PrimaryAttackDamageEvent, 
				GunOwnerController, 
				this
			);
		}
	}
}

