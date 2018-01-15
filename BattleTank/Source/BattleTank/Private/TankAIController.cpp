// Fill out your copyright notice in the Description page of Project Settings.
// Depends onf Movement component via pathfinding system

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Tank.h" // So we can impliment OnDeath

// Sets default values
ATankAIController::ATankAIController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


void ATankAIController::BeginPlay()
{ 
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{    
	Super::Tick(DeltaTime);
	   
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	 
	if (!ensure(PlayerTank &&  ControlledTank)){return;}
	MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check radius is in cm

	// Aim towards the player
	auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if(InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)){return;}

		// Subscribe outr local method to the tank's death event
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!ensure(GetPawn())) { return; } // TODO Remove if ok
	GetPawn()->DetachFromControllerPendingDestroy();
}



