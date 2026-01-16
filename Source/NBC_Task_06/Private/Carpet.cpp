// Fill out your copyright notice in the Description page of Project Settings.

#include "Carpet.h"

// Sets default values
ACarpet::ACarpet()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp =
	    CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;

	Scale = FVector(1.0f, 1.0f, 1.0f);
	StartLocation = FVector(0.0f, 0.0f, 0.0f);
	EndLocation = FVector(0.0f, 0.0f, 500.0f);
	MoveSpeed = 100.0f;
	bMovingToEnd = true;
}

void ACarpet::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(Scale);

	FVector ActorLocation = GetActorLocation();
	FRotator ActorRotation = GetActorRotation();

	WorldStartLocation = ActorLocation + ActorRotation.RotateVector(StartLocation);
	WorldEndLocation = ActorLocation + ActorRotation.RotateVector(EndLocation);

	SetActorLocation(WorldStartLocation);
}

void ACarpet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoveTowardsTarget(DeltaTime);
}

void ACarpet::MoveTowardsTarget(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector TargetLocation = bMovingToEnd ? WorldEndLocation : WorldStartLocation;

	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);

	float MoveDistance = MoveSpeed * DeltaTime;

	if (MoveDistance >= DistanceToTarget)
	{
		SetActorLocation(TargetLocation);
		bMovingToEnd = !bMovingToEnd;
	}
	else
	{
		FVector NewLocation = CurrentLocation + Direction * MoveDistance;
		SetActorLocation(NewLocation);
	}
}

