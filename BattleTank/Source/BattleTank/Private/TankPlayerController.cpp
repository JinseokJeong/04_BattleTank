// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "GameFramework/PlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerController not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing %s"), *(ControlledTank->GetName()));
	}
}

void ATankPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	// UE_LOG(LogTemp, Warning, TEXT("Player controller ticking"));
	AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }

	FVector OutHitLocation;
	if (IsSightRayHitLocation(OutHitLocation))
	{
		UE_LOG(LogTemp, Warning, TEXT("Look direction : %s"), *OutHitLocation.ToString());
		// TODO Tell controlled tank to aim at that point 
		
	}
}

bool ATankPlayerController::IsSightRayHitLocation(FVector& OutHitLocation)
{
	OutHitLocation = FVector(1.f, 1.f, 1.f);
	return true;
}