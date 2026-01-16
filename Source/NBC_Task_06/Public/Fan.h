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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly,
	          Category = "Fan|Properties")
	float RotationSpeed;

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
