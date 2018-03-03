#pragma once

#include "AbyleRWGenerator.h"
#include "RuntimeMeshComponent.h"

#include "ARWWorldMeshData.generated.h"

USTRUCT()
struct FARWWorldMeshData
{
    GENERATED_USTRUCT_BODY()
    TArray<FRuntimeMeshVertexSimple> Vertices;

    UPROPERTY()
    TArray<int32> Triangles;
};