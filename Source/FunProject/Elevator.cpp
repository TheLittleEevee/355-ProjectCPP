// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TheRoot = CreateDefaultSubobject<USceneComponent>(FName("TheRoot"));
	RootComponent = TheRoot;

	MovingRoot = CreateDefaultSubobject<USceneComponent>(FName("MovingRoot"));
	MovingRoot->SetupAttachment(TheRoot);

	TheFloor = CreateDefaultSubobject<UStaticMeshComponent>(FName("TheFloor"));
	TheFloor->SetupAttachment(MovingRoot);

	TheFrame = CreateDefaultSubobject<UInstancedStaticMeshComponent>(FName("TheFrame"));
	TheFrame->SetupAttachment(TheRoot);

	ConstructorHelpers::FObjectFinder<UStaticMesh> TheCubeMesh(TEXT("/Game/Art/Meshes/1M_Cube"));

	if (TheCubeMesh.Object)
	{
		TheFloor->SetStaticMesh(TheCubeMesh.Object);
		TheFrame->SetStaticMesh(TheCubeMesh.Object);
	}

	CurrentLocation = TheFloor->GetRelativeLocation();
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentLocation.Z += speed * DeltaTime;
	if (CurrentLocation.Z >= HeightOfElevator)
	{
		speed = 0;
		CurrentLocation.Z = HeightOfElevator;
	}
	if (CurrentLocation.Z <= 0)
	{
		speed = 0;
		CurrentLocation.Z = 0;
	}
	TheFloor->SetRelativeLocation(CurrentLocation);
}

void AElevator::OnConstruction(const FTransform& xform)
{
	Super::OnConstruction(xform);

	TheFloor->SetWorldScale3D(FVector(WidthOfElevator, DepthOfElevator, 50) / 100);

	TheFloor->SetRelativeLocation(FVector(0, 0, 0));

	//MovingRoot->SetRelativeLocation(FVector(0, 0, 0));

	TheFrame->ClearInstances();


	TheFrame->AddInstance(FTransform(FRotator(0, 0, 0), FVector(WidthOfElevator / 2 + 50 / 2, 0, HeightOfElevator / 2), FVector(50, DepthOfElevator, HeightOfElevator) / 100));
	TheFrame->AddInstance(FTransform(FRotator(0, 0, 0), FVector(-WidthOfElevator / 2 - 50 / 2, 0, HeightOfElevator / 2), FVector(50, DepthOfElevator, HeightOfElevator) / 100));
	TheFrame->AddInstance(FTransform(FRotator(0, 0, 0), FVector(0, -DepthOfElevator / 2 - 50 / 2, HeightOfElevator / 2), FVector(WidthOfElevator, 50, HeightOfElevator) / 100));
}

void AElevator::Interact()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "Player interacted with elevator");


	if (TheFloor->GetRelativeLocation() == FVector(0, 0, 0))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "At start");

		speed = 300;

		//TheFloor->MoveComponent(FVector(0, 0, HeightOfElevator), FRotator(TheFloor->GetRelativeRotation()), false);
		
	}
	else if (TheFloor->GetRelativeLocation() == FVector(0, 0, HeightOfElevator))
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Green, "At top");

		speed = -300;

		//TheFloor->MoveComponent(FVector(0, 0, -HeightOfElevator), FRotator(TheFloor->GetRelativeRotation()), false);
		
	}
	else
	{
		if (speed == 300) speed = -300;
		else speed = 300;
	}
}