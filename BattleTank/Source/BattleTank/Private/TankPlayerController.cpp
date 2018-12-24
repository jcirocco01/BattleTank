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
		GetControlledTank()->AimAt(HitLocation);

		
			//TODO tell tank to aim at crosshair
	}
}

//get world location through crosshair //true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// find crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	auto ScreenLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	//deproject the screen position to world direction
	FVector LookDirection;
	FVector WorldLocation;
	if (GetLookDirection(ScreenLocation, LookDirection, WorldLocation)) {
	//line trace along look direction and see what is hit (up to max range)
		(GetLookVectorHitLocation(LookDirection, WorldLocation, HitLocation));
			}
	else { return false; }

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection, FVector& WorldLocation) const
{
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector WorldLocation, FVector& HitLocation) const
{
	FHitResult Target;
	auto StartLocation = WorldLocation;
	auto EndLocation = StartLocation + (LookDirection*LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(
			Target,
			StartLocation,
			EndLocation,
			ECollisionChannel::ECC_Visibility))
	{		
			HitLocation = Target.Location;
			return true; 
	}
	else {
		HitLocation = FVector(0);
		return false; }
}

