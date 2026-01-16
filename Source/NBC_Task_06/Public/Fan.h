// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fan.generated.h"

UCLASS()
class NBC_TASK_06_API AFan : public AActor
{
	GENERATED_BODY()
	
public:	
	AFan();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
	          Category = "Fan|Components")
	USceneComponent* SceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Fan|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Fan|Transform",
	          meta = (ClampMin = "0.01", ClampMax = "100.0"))
	FVector Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Fan|Rotation",
	          meta = (ClampMin = "-10000.0", ClampMax = "10000.0"))
	float RotationSpeed;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
