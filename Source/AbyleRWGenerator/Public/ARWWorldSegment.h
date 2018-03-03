// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "RuntimeMeshComponent.h"
#include "ARWWorldMeshData.h"

#include "ARWWorldSegment.generated.h"

UCLASS()
class AARWWorldSegment : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARWWorldSegment();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

    void Spawn(FARWWorldMeshData& worldMeshData);
    void SetMaterial(UMaterialInterface* Material);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	USphereComponent* SphereComponent;
    URuntimeMeshComponent* meshComponent;
};
