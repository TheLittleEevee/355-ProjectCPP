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

	ElevatorAnim = CreateDefaultSubobject<UTimelineComponent>(FName("Elevator movement timeline"));

	ConstructorHelpers::FObjectFinder<UStaticMesh> TheCubeMesh(TEXT("/Game/Art/Meshes/1M_Cube"));

	if (TheCubeMesh.Object)
	{
		TheFloor->SetStaticMesh(TheCubeMesh.Object);
		TheFrame->SetStaticMesh(TheCubeMesh.Object);
	}

	CurrentLocation = TheFloor->GetRelativeLocation();
}

void AElevator::OnAnimUpdate(float val)
{
	//FRotator rot(0, val * 90, 0);
	//if (IsDoorFlipped) rot.Yaw *= -1;
	//TheHinge->SetRelativeRotation(rot);

	FVector vec(0, 0, val * HeightOfElevator);
	MovingRoot->SetRelativeLocation(vec);
}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	
	if (moveCurve)
	{
		FOnTimelineFloat eventHandler;
		eventHandler.BindUFunction(this, TEXT("OnAnimUpdate"));
		//eventHandler.BindDynamic(this, &ADoor::OnAnimUpdate);
		ElevatorAnim->AddInterpFloat(moveCurve, eventHandler, FName("Handle curve func"));
		ElevatorAnim->SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame); //Set to use last keyframe as time of timeline
	}
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/**
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
	**/
}

void AElevator::OnConstruction(const FTransform& xform)
{
	Super::OnConstruction(xform);

	TheFloor->SetWorldScale3D(FVector(WidthOfElevator, DepthOfElevator, 50) / 100);

	TheFrame->ClearInstances();


	TheFrame->AddInstance(FTransform(FRotator(0, 0, 0), FVector(WidthOfElevator / 2 + 50 / 2, 0, HeightOfElevator / 2), FVector(50, DepthOfElevator, HeightOfElevator) / 100));
	TheFrame->AddInstance(FTransform(FRotator(0, 0, 0), FVector(-WidthOfElevator / 2 - 50 / 2, 0, HeightOfElevator / 2), FVector(50, DepthOfElevator, HeightOfElevator) / 100));
	TheFrame->AddInstance(FTransform(FRotator(0, 0, 0), FVector(0, -DepthOfElevator / 2 - 50 / 2, HeightOfElevator / 2), FVector(WidthOfElevator, 50, HeightOfElevator) / 100));
}

void AElevator::Interact()
{
	/**
	if (TheFloor->GetRelativeLocation() == FVector(0, 0, 0))
	{
		speed = 300;
	}
	else if (TheFloor->GetRelativeLocation() == FVector(0, 0, HeightOfElevator))
	{
		speed = -300;
	}
	else
	{
		if (speed == 300) speed = -300;
		else speed = 300;
	}
	**/

	if (goingDown)
	{
		ElevatorAnim->Reverse();
		goingDown = false;
	}
	else
	{
		ElevatorAnim->Play();
		goingDown = true;

	}
}