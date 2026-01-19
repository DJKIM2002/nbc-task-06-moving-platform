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

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
        TEXT("/Game/Isometric-Interiors/Meshes/SM_Couch_2B.SM_Couch_2B"));
    if (MeshAsset.Succeeded()) {
        StaticMeshComp->SetStaticMesh(MeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(
        TEXT("/Game/Isometric-Interiors/Materials/"
                "M_Texture_Atlas.M_Texture_Atlas"));
    if (MaterialAsset.Succeeded()) {
        StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
    }

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

