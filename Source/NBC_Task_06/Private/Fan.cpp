// Fill out your copyright notice in the Description page of Project Settings.

#include "Fan.h"

// Sets default values
AFan::AFan()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp =
	    CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(
        TEXT("/Game/Isometric-Interiors/Meshes/SM_Fan.SM_Fan"));
    if (MeshAsset.Succeeded()) {
        StaticMeshComp->SetStaticMesh(MeshAsset.Object);
    }

    static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(
        TEXT("/Game/Isometric-Interiors/Materials/M_Texture_Atlas.M_Texture_Atlas"));
    if (MaterialAsset.Succeeded()) {
        StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
    }

	PrimaryActorTick.bCanEverTick = true;
	Scale = FVector(1.0f, 1.0f, 1.0f);
	RotationSpeed = 180.0f;
}

void AFan::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(Scale);
}

void AFan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 
			0.0f));
	}
}

