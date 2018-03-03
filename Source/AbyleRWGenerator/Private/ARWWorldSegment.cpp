// Fill out your copyright notice in the Description page of Project Settings.

#include "ARWWorldSegment.h"

// Sets default values
AARWWorldSegment::AARWWorldSegment()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
}

// Called when the game starts or when spawned
void AARWWorldSegment::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AARWWorldSegment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
TArray<FRuntimeMeshVertexSimple> Vertices;
TArray<int32> Triangles;

void AARWWorldSegment::Spawn(FARWWorldMeshData& worldMeshData)
{
	FString compName = "RMC" + FString::FromInt(1);
	meshComponent = NewObject<URuntimeMeshComponent>(this, URuntimeMeshComponent::StaticClass(), *compName);

	if (meshComponent) {
		meshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
		meshComponent->RegisterComponent();

		meshComponent->CreateMeshSection(0, worldMeshData.Vertices, worldMeshData.Triangles, true, EUpdateFrequency::Infrequent);
        meshComponent->SetMeshSectionCollisionEnabled(0, true);
        meshComponent->SetMeshSectionCastsShadow(0, true);
        UE_LOG(LogTemp, Log, TEXT("AARWWorldSegment::Spawn(FARWWorldMeshData& worldMeshData): Spawn of AbyleRWWorldSegment successful"));
	} else {
        UE_LOG(LogTemp, Error, TEXT("AARWWorldSegment::Spawn(FARWWorldMeshData& worldMeshData): Could not spawn the meshComponent"));
	}
}

void AARWWorldSegment::SetMaterial(UMaterialInterface* Material)
{
    if (Material) {
        meshComponent->SetMaterial(0, Material);
    }
}
