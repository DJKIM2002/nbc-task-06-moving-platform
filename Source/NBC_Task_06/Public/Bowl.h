// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bowl.generated.h"

UCLASS()
class NBC_TASK_06_API ABowl : public AActor
{
	GENERATED_BODY()
	
public:	
	ABowl();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
	          Category = "Bowl|Components")
	USceneComponent* SceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Bowl|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Bowl|Transform",
	          meta = (ClampMin = "0.01", ClampMax = "100.0"))
	FVector Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Bowl|Rotation",
	          meta = (ClampMin = "-1000.0", ClampMax = "1000.0"))
	float RotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Bowl|Movement",
	          meta = (ClampMin = "0.0", ClampMax = "10000.0"))
	float RandomMoveDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Bowl|Movement",
	          meta = (ClampMin = "0.1", ClampMax = "60.0"))
	float MoveInterval;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Bowl|Movement",
	          meta = (ClampMin = "0.0", ClampMax = "10000.0"))
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Bowl|Spawn",
	          meta = (ClampMin = "-100000.0", ClampMax = "100000.0"))
	float SpawnRangeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Bowl|Spawn",
	          meta = (ClampMin = "-100000.0", ClampMax = "100000.0"))
	float SpawnRangeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Bowl|Spawn",
	          meta = (ClampMin = "0.0", ClampMax = "100000.0"))
	float MinSpawnHeight;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle MoveTimerHandle;
	FVector TargetLocation;
	bool bMovingToTarget;
	
	void RotateYaw(float DeltaTime);
	void SetNewRandomTarget();
	void MoveTowardsTarget(float DeltaTime);

public:
	// Setter 함수들
	FORCEINLINE void SetRotationSpeed(float NewSpeed) { RotationSpeed = NewSpeed; }
	FORCEINLINE void SetMoveSpeed(float NewSpeed) { MoveSpeed = NewSpeed; }
};
