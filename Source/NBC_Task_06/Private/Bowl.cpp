// Fill out your copyright notice in the Description page of Project Settings.


#include "Bowl.h"

// Sets default values
ABowl::ABowl()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp =
	    CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Scale = FVector(1.0f, 1.0f, 1.0f);
	RotationSpeed = 90.0f;
	RandomMoveDistance = 200.0f;
	MoveInterval = 3.0f;
	MoveSpeed = 100.0f;
	SpawnRangeX = 2000.0f;
	SpawnRangeY = 2000.0f;
	MinSpawnHeight = 100.0f;
	bMovingToTarget = false;
}

// Called when the game starts or when spawned
void ABowl::BeginPlay()
{
	Super::BeginPlay();
	
	SetActorScale3D(Scale);

	// 랜덤한 위치에 생성 (바닥보다 위)
	FVector CurrentLocation = GetActorLocation();
	float RandomX = FMath::RandRange(-SpawnRangeX, SpawnRangeX);
	float RandomY = FMath::RandRange(-SpawnRangeY, SpawnRangeY);
	float RandomZ = FMath::Max(CurrentLocation.Z, MinSpawnHeight);
	
	SetActorLocation(FVector(CurrentLocation.X + RandomX, CurrentLocation.Y + RandomY, RandomZ));

	// 타이머 설정: 3초마다 SetNewRandomTarget 호출
	GetWorld()->GetTimerManager().SetTimer(
		MoveTimerHandle,
		this,
		&ABowl::SetNewRandomTarget,
		MoveInterval,
		true  // 반복
	);
}

// Called every frame
void ABowl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RotateYaw(DeltaTime);
	
	if (bMovingToTarget)
	{
		MoveTowardsTarget(DeltaTime);
	}
}

void ABowl::RotateYaw(float DeltaTime)
{
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		FRotator CurrentRotation = GetActorRotation();
		CurrentRotation.Yaw += RotationSpeed * DeltaTime;
		SetActorRotation(CurrentRotation);
	}
}

void ABowl::SetNewRandomTarget()
{
	// 랜덤한 방향으로 목표 위치 설정
	FVector RandomDirection = FVector(
		FMath::RandRange(-1.0f, 1.0f),
		FMath::RandRange(-1.0f, 1.0f),
		0.0f  // Z축은 변경하지 않음 (바닥 위 유지)
	).GetSafeNormal();

	FVector CurrentLocation = GetActorLocation();
	TargetLocation = CurrentLocation + RandomDirection * RandomMoveDistance;
	
	// Z축은 최소 높이 이상 유지
	TargetLocation.Z = FMath::Max(CurrentLocation.Z, MinSpawnHeight);
	
	bMovingToTarget = true;
}

void ABowl::MoveTowardsTarget(float DeltaTime)
{
	FVector CurrentLocation = GetActorLocation();
	FVector Direction = (TargetLocation - CurrentLocation).GetSafeNormal();
	float DistanceToTarget = FVector::Dist(CurrentLocation, TargetLocation);

	float MoveDistance = MoveSpeed * DeltaTime;

	if (MoveDistance >= DistanceToTarget)
	{
		SetActorLocation(TargetLocation);
		bMovingToTarget = false;
	}
	else
	{
		FVector NewLocation = CurrentLocation + Direction * MoveDistance;
		SetActorLocation(NewLocation);
	}
}

