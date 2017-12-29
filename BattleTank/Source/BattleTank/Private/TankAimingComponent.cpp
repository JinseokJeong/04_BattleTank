// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if(!BarrelToSet){return;}
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
	if(!TurretToSet){return;}
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector OutHitLocation, float LaunchSpeed)
{
	if (!Barrel) {return;}

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Calculate the OutLaunchVelocity
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		OutLaunchVelocity,
		StartLocation,
		OutHitLocation,
		LaunchSpeed,
		false,
		0,
		0, 
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	
	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveTowards(AimDirection);
	}
	

}

void UTankAimingComponent::MoveTowards(FVector AimDirection)
{
	auto Rotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotaor = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotaor - Rotator;

	Barrel->Elevate(DeltaRotator.Pitch);
	Turret->Rotate(DeltaRotator.Yaw);
}

