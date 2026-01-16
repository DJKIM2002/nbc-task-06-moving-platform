// Fill out your copyright notice in the Description page of Project Settings.


#include "Couch.h"

// Sets default values
ACouch::ACouch()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp =
	    CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	PrimaryActorTick.bCanEverTick = true;

	Scale = FVector(1.0f, 1.0f, 1.0f);
	RotationSpeed = 90.0f;
}

void ACouch::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorScale3D(Scale);
}

void ACouch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateYaw(DeltaTime);
}

void ACouch::RotateYaw(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	float YawDelta = RotationSpeed * DeltaTime;
	
	CurrentRotation.Yaw += YawDelta;
	
	SetActorRotation(CurrentRotation);
}

