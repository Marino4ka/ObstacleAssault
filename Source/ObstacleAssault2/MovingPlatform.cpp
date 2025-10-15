// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("START GAME in  %f sec"), 3.333);

	StartLocation = GetActorLocation();

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);

}

void AMovingPlatform::MovePlatform(float DT)
{
	DistanceMoved = GetDistanceMoved();

	if(DistanceMoved >= MoveDistance)
	{
		float Overshoot = DistanceMoved - MoveDistance;
		FString PlatformName = GetName();
		UE_LOG(LogTemp, Display, TEXT("%s Overshoot is %f"), *PlatformName, Overshoot);

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		FVector NewStartLocation = StartLocation + MoveDirection * MoveDistance;

		SetActorLocation(NewStartLocation);

		StartLocation = NewStartLocation;

		PlatformVelocity = -PlatformVelocity;

	}
	else
	{
		FVector CurrentLocation = GetActorLocation();

		CurrentLocation = CurrentLocation + (PlatformVelocity * DT);

		SetActorLocation(CurrentLocation);
	}

}

float AMovingPlatform::GetDistanceMoved()
{
	return FVector::Dist(StartLocation, GetActorLocation());
}

void AMovingPlatform::RotatePlatform(float DT)
{
	/*
	FRotator CurrentRotation = GetActorRotation(); 

	CurrentRotation = CurrentRotation + (RotationVelocity * DT);

	SetActorRotation(CurrentRotation);
	*/

	FRotator RotationToAdd = RotationVelocity * DT;
	AddActorLocalRotation(RotationToAdd);
}


