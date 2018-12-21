// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "../Public/TankPlayerController.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	if (!ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("Player Controlling not posessing Tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player Controlling %s"), *(ControlledTank->GetName()))
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if (!GetControlledTank()) { return; }

	FVector HitLocation; // Out Paramater
	if (GetSightRayHitLocation(HitLocation))
	{
		//UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

		
			//TODO tell tank to aim at crosshair
	}
}

//get world location through crosshair //true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//deproject the screen position to world direction

	//line trace along look direction and see what is hit (up to max range)

	return true;
}

