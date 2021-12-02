// Fill out your copyright notice in the Description page of Project Settings.


#include "DisappearingPlatform.h"

// Sets default values
ADisappearingPlatform::ADisappearingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TheRoot = CreateDefaultSubobject<USceneComponent>(FName("TheRoot"));
	RootComponent = TheRoot;

	ThePlatform = CreateDefaultSubobject<UStaticMeshComponent>(FName("ThePlatform"));
	ThePlatform->SetupAttachment(TheRoot);

	ConstructorHelpers::FObjectFinder<UStaticMesh> TheCubeMesh(TEXT("/Game/Art/Meshes/1M_Cube"));

	if (TheCubeMesh.Object)
	{
		ThePlatform->SetStaticMesh(TheCubeMesh.Object);
	}
}

// Called when the game starts or when spawned
void ADisappearingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	if (startNormal)
	{
		counter = 0;
	}
	else
	{
		counter = changeTimer;
	}
}

// Called every frame
void ADisappearingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	counter += DeltaTime;

	if (counter >= changeTimer * 2)
	{
		ThePlatform->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ThePlatform->SetMaterial(0, NormalMaterial);
		counter = 0;
	}
	else if (counter >= changeTimer)
	{
		ThePlatform->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		ThePlatform->SetMaterial(0, InvisMaterial);
	}
	else
	{
		ThePlatform->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		ThePlatform->SetMaterial(0, NormalMaterial);
	}
}

void ADisappearingPlatform::OnConstruction(const FTransform& xform)
{
	Super::OnConstruction(xform);

	ThePlatform->SetWorldScale3D(FVector(WidthOfPlat, DepthOfPlat, HeightOfPlat) / 100);
}