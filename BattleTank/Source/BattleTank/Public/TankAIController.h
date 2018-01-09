// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

// Forward Declarations
class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
	
public:
	
	ATankAIController();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// How close can the AI tank get to
	float AcceptanceRadius = 3000;
	
};
