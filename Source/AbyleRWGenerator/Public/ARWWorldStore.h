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

    void Setup(const FString& pointsFile);

private:
    bool GetFromFile();

    FString m_pointsFile;
};
