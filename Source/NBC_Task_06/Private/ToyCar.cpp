// Fill out your copyright notice in the Description page of Project Settings.

#include "ToyCar.h"

// Sets default values
AToyCar::AToyCar() 
{
  SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
  SetRootComponent(SceneRoot);

  StaticMeshComp =
      CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
  StaticMeshComp->SetupAttachment(SceneRoot);
  StaticMeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

  static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
      TEXT("/Game/Furniture_Free/Meshes/SM_toy_001.SM_toy_001"));
  if (MeshAsset.Succeeded()) {
    StaticMeshComp->SetStaticMesh(MeshAsset.Object);
  }

  static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(
      TEXT("/Game/Furniture_Free/Materials/M_Material.M_Material"));
  if (MaterialAsset.Succeeded()) {
    StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
  }

  PrimaryActorTick.bCanEverTick = true;
  
  Scale = FVector(1.0f, 1.0f, 1.0f);
  StartLocationX = 0.0f;
  EndLocationX = 1000.0f;
  MoveSpeed = 200.0f;
  bMovingToEnd = true;
}

void AToyCar::BeginPlay() 
{
  Super::BeginPlay();

  SetActorScale3D(Scale);

  FVector ActorLocation = GetActorLocation();
  
  StartLocation = FVector(ActorLocation.X + StartLocationX, ActorLocation.Y, ActorLocation.Z);
  EndLocation = FVector(ActorLocation.X + EndLocationX, ActorLocation.Y, ActorLocation.Z);

  SetActorLocation(StartLocation);
  
  if (EndLocationX > StartLocationX)
  {
    SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
  }
  else
  {
    SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
  }
}

void AToyCar::Tick(float DeltaTime) 
{
  Super::Tick(DeltaTime);

  MoveTowardsTarget(DeltaTime);
}

void AToyCar::MoveTowardsTarget(float DeltaTime)
{
  FVector CurrentLocation = GetActorLocation();
  FVector TargetLocation = bMovingToEnd ? EndLocation : StartLocation;
  
  FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
  float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);
  
  float MoveDistance = MoveSpeed * DeltaTime;
  
  if (MoveDistance >= DistanceToTarget)
  {
    SetActorLocation(TargetLocation);
    
    bMovingToEnd = !bMovingToEnd;
    
    if (bMovingToEnd)
    {
      SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
    }
    else
    {
      SetActorRotation(FRotator(0.0f, 180.0f, 0.0f));
    }
  }
  else
  {
    FVector NewLocation = CurrentLocation + Direction * MoveDistance;
    SetActorLocation(NewLocation);
  }
}