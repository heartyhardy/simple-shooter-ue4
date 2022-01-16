// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Controller.h"

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

	UGameplayStatics::SpawnSoundAttached(
		MuzzleSound,
		Mesh,
		TEXT("MuzzleFlashSocket")
	);

	FVector ShotDirection;
	FHitResult Hit;
	bool bHit = GunTrace(Hit, ShotDirection);

	if(bHit && BulletImpactParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			GetWorld(),
			BulletImpactParticles,
			Hit.Location,
			ShotDirection.Rotation()
		);

		UGameplayStatics::SpawnSoundAtLocation(
			GetWorld(),
			ImpactSound,
			Hit.Location,
			ShotDirection.Rotation()
		);

		AActor* ActorGotHit = Hit.GetActor();

		if(ActorGotHit)
		{
			FPointDamageEvent PrimaryAttackDamageEvent(PrimaryAttackDamage, Hit, ShotDirection, nullptr);
			
			AController* GunOwnerController = GetGunController();
			
			ActorGotHit->TakeDamage(
				PrimaryAttackDamage, 
				PrimaryAttackDamageEvent, 
				GunOwnerController, 
				this
			);
		}
	}
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{

	AController* GunOwnerController = GetGunController();

	if(!GunOwnerController) return false;

	FVector Location;
	FRotator Rotation;

	GunOwnerController->GetPlayerViewPoint(out Location, out Rotation);
	
	ShotDirection = -Rotation.Vector();

	FVector GunMaxRange = Location + Rotation.Vector() * MaxRange;

	FCollisionQueryParams CollisionParams;

	//Exclude Gun and Character from collison or it will shoot itself
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(GetOwner());

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		Hit,
		Location,
		GunMaxRange,
		ECollisionChannel::ECC_GameTraceChannel1,
		CollisionParams
	);

	return bHit;
}

AController* AGun::GetGunController() const
{
	APawn* GunOwner = Cast<APawn>(GetOwner());
	if(!GunOwner) return nullptr;

	AController* GunOwnerController = GunOwner->GetController();
	return GunOwnerController;
}