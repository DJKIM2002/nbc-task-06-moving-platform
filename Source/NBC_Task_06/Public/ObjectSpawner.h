// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectSpawner.generated.h"

UCLASS()
class NBC_TASK_06_API AObjectSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AObjectSpawner();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Spawner|Settings")
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Spawner|Settings",
	          meta = (ClampMin = "1", ClampMax = "100"))
	int32 SpawnCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Spawner|Spawn Range",
	          meta = (ClampMin = "-100000.0", ClampMax = "100000.0"))
	float SpawnRangeX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Spawner|Spawn Range",
	          meta = (ClampMin = "-100000.0", ClampMax = "100000.0"))
	float SpawnRangeY;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Spawner|Spawn Range",
	          meta = (ClampMin = "0.0", ClampMax = "10000.0"))
	float MinSpawnHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Spawner|Spawn Range",
	          meta = (ClampMin = "0.0", ClampMax = "10000.0"))
	float MaxSpawnHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Spawner|Random Properties")
	bool bRandomizeRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Spawner|Random Properties")
	bool bRandomizeScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Spawner|Random Properties",
	          meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float MinScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Spawner|Random Properties",
	          meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float MaxScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Spawner|Random Properties")
	bool bRandomizeSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Spawner|Random Properties",
	          meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MinSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Spawner|Random Properties",
	          meta = (ClampMin = "0.0", ClampMax = "1000.0"))
	float MaxSpeed;

	virtual void BeginPlay() override;

private:
	void SpawnObjects();
	void SpawnMyObject();
};
