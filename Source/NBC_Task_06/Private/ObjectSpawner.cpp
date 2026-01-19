// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectSpawner.h"
#include "Bowl.h"
#include "Carpet.h"
#include "Couch.h"

// Sets default values
AObjectSpawner::AObjectSpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SpawnCount = 5;
	SpawnRangeX = 2000.0f;
	SpawnRangeY = 2000.0f;
	MinSpawnHeight = 100.0f;
	MaxSpawnHeight = 500.0f;
	
	bRandomizeRotation = true;
	bRandomizeScale = true;
	MinScale = 0.5f;
	MaxScale = 2.0f;
	
	bRandomizeSpeed = true;
	MinSpeed = 50.0f;
	MaxSpeed = 300.0f;
}

// Called when the game starts or when spawned
void AObjectSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	SpawnObjects();
}

void AObjectSpawner::SpawnObjects()
{
	for (int32 i = 0; i < SpawnCount; ++i)
	{
		SpawnMyObject();
	}
}

void AObjectSpawner::SpawnMyObject()
{
	if (ActorToSpawn == nullptr) return;

	// 랜덤 위치 생성
	FVector SpawnLocation = GetActorLocation();
	SpawnLocation.X += FMath::RandRange(-SpawnRangeX, SpawnRangeX);
	SpawnLocation.Y += FMath::RandRange(-SpawnRangeY, SpawnRangeY);
	SpawnLocation.Z += FMath::RandRange(MinSpawnHeight, MaxSpawnHeight);
	
	// 랜덤 회전 (0, 90, 180, 270도만 사용)
	FRotator SpawnRotation = FRotator::ZeroRotator;
	if (bRandomizeRotation)
	{
		// 0, 90, 180, 270 중 하나를 랜덤으로 선택
		TArray<float> RotationValues = {0.0f, 90.0f, 180.0f, 270.0f};
		
		SpawnRotation.Pitch = RotationValues[FMath::RandRange(0, 3)];
		SpawnRotation.Yaw = RotationValues[FMath::RandRange(0, 3)];
		SpawnRotation.Roll = RotationValues[FMath::RandRange(0, 3)];
	}

	// 액터 스폰
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
		ActorToSpawn,
		SpawnLocation,
		SpawnRotation,
		SpawnParams
	);

	// 액터 종류에 따라 랜덤 속성 적용 (Bowl, Couch, Carpet)
	if (SpawnedActor)
	{
		// Scale 랜덤화
		if (bRandomizeScale)
		{
			float RandomScale = FMath::RandRange(MinScale, MaxScale);
			SpawnedActor->SetActorScale3D(FVector(RandomScale));
		}

		// Speed 랜덤화
		if (bRandomizeSpeed)
		{
			// Bowl - RotationSpeed와 MoveSpeed
			if (ABowl* Bowl = Cast<ABowl>(SpawnedActor))
			{
				float RandomRotationSpeed = FMath::RandRange(-MaxSpeed, MaxSpeed);
				Bowl->SetRotationSpeed(RandomRotationSpeed);
				
				float RandomMoveSpeed = FMath::RandRange(MinSpeed, MaxSpeed);
				Bowl->SetMoveSpeed(RandomMoveSpeed);
			}
			// Couch - RotationSpeed
			else if (ACouch* Couch = Cast<ACouch>(SpawnedActor))
			{
				float RandomRotationSpeed = FMath::RandRange(-MaxSpeed, MaxSpeed);
				Couch->SetRotationSpeed(RandomRotationSpeed);
			}
			// Carpet - MoveSpeed
			else if (ACarpet* Carpet = Cast<ACarpet>(SpawnedActor))
			{
				float RandomMoveSpeed = FMath::RandRange(MinSpeed, MaxSpeed);
				Carpet->SetMoveSpeed(RandomMoveSpeed);
			}
		}
	}
}

