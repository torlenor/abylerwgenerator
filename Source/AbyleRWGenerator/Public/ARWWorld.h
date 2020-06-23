// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

#include "ARWWorldSegment.h"
#include "ARWWorldMeshData.h"
#include "ARWWorldStore.h"

#include "ARWWorld.generated.h"

USTRUCT()
struct ABYLERWGENERATOR_API FMeshData
{
    GENERATED_USTRUCT_BODY()
 
    public:
    // uint16 TestIntValue;
    float TestFloatValue;
 
    friend FArchive& operator<<(FArchive& Ar, FMeshData& SObj)
    {
        Ar << SObj.TestFloatValue;    
        return Ar;
    }
};

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
	bool Start(const int xSegments=2, const int ySegments=2);

    UFUNCTION(BlueprintCallable, Category = "AbyleRWGenerator")
    bool Setup(const FString pointsFile, const FString trianglesFile, const FString heightMapDirectory);

    UFUNCTION(BlueprintCallable, Category = "AbyleRWGenerator")
    bool ReadBinary();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    void RebaseWorld();

    TArray<AARWWorldSegment*> m_worldSegments;

    UPROPERTY()
    UARWWorldStore* m_worldStore;

    bool m_isSetup;
};
