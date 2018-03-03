// Fill out your copyright notice in the Description page of Project Settings.

#include "ARWWorldStore.h"

UARWWorldStore::UARWWorldStore()
{ }

UARWWorldStore::~UARWWorldStore()
{ }

void UARWWorldStore::Setup(const FString& pointsFile)
{
    m_pointsFile = pointsFile;
}

bool UARWWorldStore::GetFromFile() 
{
	FString pointsDataString = "";
	FFileHelper::LoadFileToString(pointsDataString, *m_pointsFile);
	if (pointsDataString.Len() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("Could not read points file"));
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("PointsFIle: \n %s"), *pointsDataString);

	TArray <FString> pointsLineArray;
	if (pointsDataString.ParseIntoArrayLines(pointsLineArray, true) == 0) {
		UE_LOG(LogTemp, Warning, TEXT("Could not parse points file into lines"));
        return false;
	}
    
    TArray<FVector> pointVectors;

	for (FString& line : pointsLineArray) {
		TArray<FString> lineString;
		line.ParseIntoArray(lineString, TEXT(" "), true);
        
		UE_LOG(LogTemp, Warning, TEXT("Line in Points File: \n %s"), *line);
		if (lineString.Num() != 3) {
			UE_LOG(LogTemp, Warning, TEXT("Could not parse points line into entries"));
            return false;
			break;
		}

        FVector pointCoords = FVector(FCString::Atof(*lineString[0]), FCString::Atof(*lineString[1]), FCString::Atof(*lineString[2]));
        pointVectors.Add(pointCoords);
	}

    return true;
}

FARWWorldMeshData UARWWorldStore::getWorldMeshData()
{
    GetFromFile();
    
    FARWWorldMeshData worldMeshData;

    static float m2cm=100;

    // First vertex
    worldMeshData.Vertices.Add(FRuntimeMeshVertexSimple(FVector(0, 500*m2cm, 0), FVector(0, 0, 1), FRuntimeMeshTangent(0, -1, 0), FColor::White, FVector2D(0, 0)));
    // Second vertex
    worldMeshData.Vertices.Add(FRuntimeMeshVertexSimple(FVector(500*m2cm, 500*m2cm, 0), FVector(0, 0, 1), FRuntimeMeshTangent(0, -1, 0), FColor::White, FVector2D(0, 25)));
    // Third vertex
    worldMeshData.Vertices.Add(FRuntimeMeshVertexSimple(FVector(500*m2cm, 0, 0), FVector(0, 0, 1), FRuntimeMeshTangent(0, -1, 0), FColor::White, FVector2D(25, 25)));
    // Fourth vertex
    worldMeshData.Vertices.Add(FRuntimeMeshVertexSimple(FVector(0, 0, 0), FVector(0, 0, 1), FRuntimeMeshTangent(0, -1, 0), FColor::White, FVector2D(25, 0)));

    worldMeshData.Triangles.Add(0);
    worldMeshData.Triangles.Add(1);
    worldMeshData.Triangles.Add(2);
    worldMeshData.Triangles.Add(0);
    worldMeshData.Triangles.Add(2);
    worldMeshData.Triangles.Add(3);

    return worldMeshData;
}
