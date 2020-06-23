// Fill out your copyright notice in the Description page of Project Settings.

#include "ARWWorld.h"

// Sets default values
AARWWorld::AARWWorld() :
    m_isSetup{false}
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AARWWorld::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AARWWorld::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    RebaseWorld();
}

bool AARWWorld::Setup(FString pointsFile, FString trianglesFile, FString heightMapDirectory) 
{
    m_worldStore = NewObject<UARWWorldStore>(this);

    if (m_worldStore) {
        m_isSetup = m_worldStore->Setup(pointsFile, heightMapDirectory);
        return m_isSetup;
    } else {
        return false;
    }
}

bool AARWWorld::Start(const int xSegments, const int ySegments)
{
    if (!m_isSetup) {
        return false;
    }

    static float m2cm=100;

    for (int i=0; i<xSegments; i++) {
        for (int j=0; j<ySegments; j++) {

            FARWWorldMeshData worldMeshData = m_worldStore->getWorldMeshData(i, j);
            //FARWWorldMeshData worldMeshData = m_worldStore->getWorldMeshData();

	        //AARWWorldSegment* segment = GetWorld()->SpawnActor<AARWWorldSegment>(AARWWorldSegment::StaticClass(), 
            //                                                                     FVector(-500.0f*m2cm + i*500.0f*m2cm, -500.0f*m2cm + j*500.0f*m2cm, 10.0f), 
            //                                                                     FRotator(0.0f));

	        AARWWorldSegment* segment = GetWorld()->SpawnActor<AARWWorldSegment>(AARWWorldSegment::StaticClass(), 
                                                                                 FVector( -m2cm*5000*xSegments/2.0f + 0.0f, -m2cm*5000*xSegments/2.0f + 0.0f, 10.0f), 
                                                                                 FRotator(0.0f));

            if (segment) {
                segment->Spawn(worldMeshData);
                if (Material) {
                    segment->SetMaterial(Material);
                }
                m_worldSegments.Add(segment);
            } else {
                UE_LOG(LogTemp, Error, TEXT("AARWWorld::start(): Could not spawn the AbyleRWWorldSegment"));
                return false;
            }
        }
    }

    return true;
}

bool AARWWorld::ReadBinary()
{
    FString binaryFile = "H:/git/QWorldParser/output/binary/test.bin";

    TArray<uint8> inBinaryArray;
    FFileHelper::LoadFileToArray(inBinaryArray, *binaryFile);
    FMemoryReader FromBinary = FMemoryReader(inBinaryArray, true); //true, free data after done
    FromBinary.Seek(0);
 
    FMeshData meshData;

    FromBinary << meshData;

    UE_LOG(LogTemp, Error, TEXT("AARWWorld::ReadBinary(): Read: %f"), meshData.TestFloatValue);

    FromBinary.FlushCache();
    inBinaryArray.Empty();
    FromBinary.Close(); 

    return true;
}

void AARWWorld::RebaseWorld()
{
    // FVector G = GetActorLocation();

    // ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    FVector G = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

    UWorld* World = GetWorld();
    // if (FMath::Abs(G.X) > 50000 || FMath::Abs(G.Y) > 50000 ) // || FMath::Abs(G.Z) > 50000)
    if (FMath::Abs(G.X) > 500000 || FMath::Abs(G.Y) > 500000 ) // || FMath::Abs(G.Z) > 50000)
    {
        UE_LOG(LogTemp, Error, TEXT("AARWWorld::RebaseWorld(): Rebased!"));
	    World->SetNewWorldOrigin(FIntVector(G.X, G.Y, 0.0f) + World->OriginLocation);
    }
}