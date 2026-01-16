// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Couch.generated.h"

UCLASS()
class NBC_TASK_06_API ACouch : public AActor
{
	GENERATED_BODY()
	
public:	
	ACouch();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,
	          Category = "Couch|Components")
	USceneComponent* SceneRoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Couch|Components")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Couch|Transform",
	          meta = (ClampMin = "0.01", ClampMax = "100.0"))
	FVector Scale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,
	          Category = "Couch|Rotation",
	          meta = (ClampMin = "-1000.0", ClampMax = "1000.0"))
	float RotationSpeed;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	// Setter 함수
	FORCEINLINE void SetRotationSpeed(float NewSpeed) { RotationSpeed = NewSpeed; }

private:
	void RotateYaw(float DeltaTime);
};
