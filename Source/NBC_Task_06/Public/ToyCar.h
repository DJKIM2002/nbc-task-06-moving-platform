// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ToyCar.generated.h"

UCLASS()
class NBC_TASK_06_API AToyCar : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AToyCar();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
                Category = "ToyCar|Components")
	USceneComponent* SceneRoot;
    UPROPERTY(EditAnywhere, BlueprintReadWrite,
                Category = "ToyCar|Components")
    UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "ToyCar|Movement",
	          meta = (ClampMin = "-100000.0", ClampMax = "100000.0"))
	float StartLocationX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "ToyCar|Movement",
	          meta = (ClampMin = "-100000.0", ClampMax = "100000.0"))
	float EndLocationX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "ToyCar|Movement")
	float MoveSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
	          Category = "ToyCar|Movement")
	bool bMovingToEnd;

	void BeginPlay() override;
    void Tick(float DeltaTime) override;

private:
	FVector StartLocation;
	FVector EndLocation;
	
	void MoveTowardsTarget(float DeltaTime);
};
