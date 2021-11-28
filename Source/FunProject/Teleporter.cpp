// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter.h"

// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TheRoot = CreateDefaultSubobject<USceneComponent>(FName("TheRoot"));
	RootComponent = TheRoot;

	DestinationRoot = CreateDefaultSubobject<USceneComponent>(FName("DestinationRoot"));
	DestinationRoot->SetupAttachment(TheRoot);

	TheDestination = CreateDefaultSubobject<UStaticMeshComponent>(FName("TheDestination"));
	TheDestination->SetupAttachment(DestinationRoot);

	TeleporterPad = CreateDefaultSubobject<UInstancedStaticMeshComponent>(FName("TeleporterPad"));
	TeleporterPad->SetupAttachment(TheRoot);

	ConstructorHelpers::FObjectFinder<UStaticMesh> TheCubeMesh(TEXT("/Game/Art/Meshes/1M_Cube"));

	if (TheCubeMesh.Object)
	{
		TheDestination->SetStaticMesh(TheCubeMesh.Object);
		TeleporterPad->SetStaticMesh(TheCubeMesh.Object);
	}

}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATeleporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleporter::OnConstruction(const FTransform& xform)
{
	Super::OnConstruction(xform);

	TheDestination->SetWorldScale3D(FVector(WidthOfPad, DepthOfPad, 25) / 100);

	TeleporterPad->ClearInstances();

	TeleporterPad->AddInstance(FTransform(FRotator(0, 0, 0), FVector(0, 0, 0), FVector(WidthOfPad, DepthOfPad, 25) / 100));
	TeleporterPad->AddInstance(FTransform(FRotator(0, 0, 0), FVector(WidthOfPad / 2 + 50 / 2, 0, HeightOfPad / 2), FVector(50, DepthOfPad, HeightOfPad) / 100));
	TeleporterPad->AddInstance(FTransform(FRotator(0, 0, 0), FVector(-WidthOfPad / 2 - 50 / 2, 0, HeightOfPad / 2), FVector(50, DepthOfPad, HeightOfPad) / 100));
	TeleporterPad->AddInstance(FTransform(FRotator(0, 0, 0), FVector(0, -DepthOfPad / 2 - 50 / 2, HeightOfPad / 2), FVector(WidthOfPad, 50, HeightOfPad) / 100));
}

void ATeleporter::Interact()
{
	GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorLocation(DestinationRoot->GetComponentLocation() + FVector(0, 0, 100));

	//GetWorld()->GetFirstPlayerController()->GetPawn()->SetActorRotation(FRotator(0, 180, 0));
}