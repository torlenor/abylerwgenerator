// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

#include "ARWWorldSegment.h"
#include "ARWWorldMeshData.h"
#include "ARWWorldStore.h"

#include "ARWWorld.generated.h"

UCLASS()
class ABYLERWGENERATOR_API AARWWorld : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AARWWorld();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AbyleRWGenerator")
	UMaterialInterface* Material;

	UFUNCTION(BlueprintCallable, Category = "AbyleRWGenerator")
	bool Start();

    UFUNCTION(BlueprintCallable, Category = "AbyleRWGenerator")
    bool Setup(FString pointsFile, FString trianglesFile);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    TArray<AARWWorldSegment*> m_worldSegments;

    UPROPERTY()
    UARWWorldStore* m_worldStore;

    bool m_isSetup;
};
