// Fill out your copyright notice in the Description page of Project Settings.

#include "ARWWorldStore.h"

UARWWorldStore::UARWWorldStore() :
    m_generated{false}
{ }

UARWWorldStore::~UARWWorldStore()
{ }

bool UARWWorldStore::Setup(const FString& pointsFile, const FString& heightMapDirectory)
{
    m_pointsFile = pointsFile;
    m_heightMapDirectory = heightMapDirectory;

    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

    if (!PlatformFile.DirectoryExists(*heightMapDirectory)) {
        UE_LOG(LogTemp, Error, TEXT("UARWWorldStore::Setup(const FString& pointsFile, const FString& heightMapDirectory): Heightmap directory %s does not exist."), *heightMapDirectory);
        return false; 
    } else {
        return true;
    }
}

bool UARWWorldStore::GetFromGridStore(FARWWorldMeshData& worldMeshData, int x, int y)
{
    FString pointsDataString = "";

    FString pointsFile = m_heightMapDirectory + FString("/heightmap_") + FString::FromInt(x) + FString("_") + FString::FromInt(y) + FString(".dat");

    UE_LOG(LogTemp, Log, TEXT("UARWWorldStore::GetFromGridStore(FARWWorldMeshData& worldMeshData, int x, int y): Loading file %s"), *pointsFile);

	FFileHelper::LoadFileToString(pointsDataString, *pointsFile);
	if (pointsDataString.Len() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("Could not read points file"));
		return false;
	}

	TArray <FString> pointsLineArray;
	if (pointsDataString.ParseIntoArrayLines(pointsLineArray, true) == 0) {
		UE_LOG(LogTemp, Warning, TEXT("Could not parse points file into lines"));
        return false;
	}
    
    TArray<FVector> vertices;

	for (FString& line : pointsLineArray) {
		TArray<FString> lineString;
		line.ParseIntoArray(lineString, TEXT(" "), true);
        
		if (lineString.Num() != 3) {
			UE_LOG(LogTemp, Warning, TEXT("Could not parse points line into entries"));
            return false;
			break;
		}

        FVector pointCoords = FVector(FCString::Atof(*lineString[0]), FCString::Atof(*lineString[1]), FCString::Atof(*lineString[2]));
        worldMeshData.Vertices.Add(FRuntimeMeshVertexSimple(pointCoords, FVector(0, 0, 1), FRuntimeMeshTangent(0, -1, 0), FColor::White, FVector2D(pointCoords[0]/20.0f, pointCoords[1]/20.0f)));
	}

    int maxX=501;
    int maxY=501;

    // TArray<int32> Triangles;
    for (int i=0; i<maxX-1 ; i++) {
        for (int j=0; j<maxY-1 ; j++) {
            int indexTopLeftVertex = j + i*maxX;
            int indexTopRightVertex = (j+1) + i*maxX;
            int indexBottomLeftVertex = j + (i+1)*maxX;
            int indexBottomRightVertex = (j+1) + (i+1)*maxX;

            // First quad triangle
            worldMeshData.Triangles.Add(indexTopLeftVertex);
            worldMeshData.Triangles.Add(indexTopRightVertex);
            worldMeshData.Triangles.Add(indexBottomLeftVertex);

            // Second quad triangle
            worldMeshData.Triangles.Add(indexTopRightVertex);
            worldMeshData.Triangles.Add(indexBottomRightVertex);
            worldMeshData.Triangles.Add(indexBottomLeftVertex);
        }
    }

    return true;
}

bool UARWWorldStore::GetFromFile(FARWWorldMeshData& worldMeshData) 
{
    if (m_generated) {
        worldMeshData = m_worldMeshData;
        return true;
    }

	FString pointsDataString = "";
	FFileHelper::LoadFileToString(pointsDataString, *m_pointsFile);
	if (pointsDataString.Len() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("Could not read points file"));
		return false;
	}
	// UE_LOG(LogTemp, Log, TEXT("PointsFIle: \n %s"), *pointsDataString);

	TArray <FString> pointsLineArray;
	if (pointsDataString.ParseIntoArrayLines(pointsLineArray, true) == 0) {
		UE_LOG(LogTemp, Warning, TEXT("Could not parse points file into lines"));
        return false;
	}
    
    TArray<FVector> vertices;

	for (FString& line : pointsLineArray) {
		TArray<FString> lineString;
		line.ParseIntoArray(lineString, TEXT(" "), true);
        
		// UE_LOG(LogTemp, Log, TEXT("Line in Points File: \n %s"), *line);
		if (lineString.Num() != 3) {
			UE_LOG(LogTemp, Warning, TEXT("Could not parse points line into entries"));
            return false;
			break;
		}

        FVector pointCoords = FVector(FCString::Atof(*lineString[0]), FCString::Atof(*lineString[1]), FCString::Atof(*lineString[2]));
        // worldMeshData.Vertices.Add(pointCoords);
        worldMeshData.Vertices.Add(FRuntimeMeshVertexSimple(pointCoords, FVector(0, 0, 1), FRuntimeMeshTangent(0, -1, 0), FColor::White, FVector2D(pointCoords[0]/20.0f, pointCoords[1]/20.0f)));
	}

    int maxX=501;
    int maxY=501;

    // TArray<int32> Triangles;
    for (int i=0; i<maxX-1 ; i++) {
        for (int j=0; j<maxY-1 ; j++) {
            int indexTopLeftVertex = j + i*maxX;
            int indexTopRightVertex = (j+1) + i*maxX;
            int indexBottomLeftVertex = j + (i+1)*maxX;
            int indexBottomRightVertex = (j+1) + (i+1)*maxX;

            // First quad triangle
            worldMeshData.Triangles.Add(indexTopLeftVertex);
            worldMeshData.Triangles.Add(indexTopRightVertex);
            worldMeshData.Triangles.Add(indexBottomLeftVertex);

            // Second quad triangle
            worldMeshData.Triangles.Add(indexTopRightVertex);
            worldMeshData.Triangles.Add(indexBottomRightVertex);
            worldMeshData.Triangles.Add(indexBottomLeftVertex);

            // UE_LOG(LogTemp, Warning, TEXT("Last index: %d"), indexBottomRightVertex);
        }
    }

    m_generated = true;
    m_worldMeshData = worldMeshData;

    return true;
} 

FARWWorldMeshData UARWWorldStore::getWorldMeshData()
{
    FARWWorldMeshData worldMeshData;
    GetFromFile(worldMeshData);

    return worldMeshData;
}

FARWWorldMeshData UARWWorldStore::getWorldMeshData(const int x, const int y)
{
    FARWWorldMeshData worldMeshData;
    GetFromGridStore(worldMeshData, x, y);

    return worldMeshData;
}
