// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "LMovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API ALMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:

	ALMovingPlatform();

protected:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere)
		float Speed = 20.0f;

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;


private:

	FVector GlobalTargetLocation;

	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;
	
public:

	void AddActiveTrigger();

	void RemoveActiveTrigger();



};
