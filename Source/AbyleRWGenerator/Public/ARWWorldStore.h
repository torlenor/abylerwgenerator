// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ARWWorldMeshData.h"

#include "ARWWorldStore.generated.h"

/**
 * 
 */
UCLASS()
class UARWWorldStore : public UObject
{
    GENERATED_BODY()

public:
	UARWWorldStore();
	~UARWWorldStore();

    FARWWorldMeshData getWorldMeshData();
    FARWWorldMeshData getWorldMeshData(const int x, const int y);

    bool Setup(const FString& pointsFile, const FString& heightMapDirectory);

private:
    bool GetFromFile(FARWWorldMeshData& worldMeshData);

    bool GetFromGridStore(FARWWorldMeshData& worldMeshData, int x, int y);

    FString m_pointsFile;
    FString m_heightMapDirectory;

    bool m_generated;

    FARWWorldMeshData m_worldMeshData;
};
