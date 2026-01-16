// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Carpet.generated.h"

UCLASS()
class NBC_TASK_06_API ACarpet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACarpet();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
	          Category = "Carpet|Components")
	USceneComponent* SceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Carpet|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Carpet|Transform",
	          meta = (ClampMin = "0.01", ClampMax = "100.0"))
	FVector Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Carpet|Movement")
	FVector StartLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Carpet|Movement")
	FVector EndLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Carpet|Movement",
	          meta = (ClampMin = "0.0", ClampMax = "10000.0"))
	float MoveSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
	          Category = "Carpet|Movement")
	bool bMovingToEnd;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	FVector WorldStartLocation;
	FVector WorldEndLocation;
	
	void MoveTowardsTarget(float DeltaTime);
};
