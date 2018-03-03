// Fill out your copyright notice in the Description page of Project Settings.

#include "ARWWorld.h"

// Sets default values
AARWWorld::AARWWorld() :
    m_isSetup{false}
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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

}

bool AARWWorld::Setup(FString pointsFile, FString trianglesFile) 
{
    m_worldStore = NewObject<UARWWorldStore>(this);

    if (m_worldStore) {
        m_worldStore->Setup(pointsFile);
        m_isSetup = true;
        return true;
    } else {
        return false;
    }
}

bool AARWWorld::Start()
{
    if (!m_isSetup) {
        return false;
    }

    static float m2cm=100;

    FARWWorldMeshData worldMeshData = m_worldStore->getWorldMeshData();

    for (int i=0; i<4; i++) {
        for (int j=0; j<4; j++) {
	        AARWWorldSegment* segment = GetWorld()->SpawnActor<AARWWorldSegment>(AARWWorldSegment::StaticClass(), 
                                                                                 FVector(2*-500.0f*m2cm + i*500.0f*m2cm, 2*-500.0f*m2cm + j*500.0f*m2cm, 10.0f), 
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

