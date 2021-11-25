// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "UObject/ConstructorHelpers.h"
#include "InteractableThing.h"

//Must always be last
#include "Door.generated.h"


UCLASS()
class FUNPROJECT_API ADoor : public AActor, public IInteractableThing
{
	GENERATED_BODY()

	

	
public:	
	// Sets default values for this actor's properties
	ADoor();

	//scene component for root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* TheRoot;

	//scene component for hinge
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* TheHinge;

	//mesh for door
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* TheMeshDoor;

	//mesh for door frame
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UInstancedStaticMeshComponent* TheMeshFrame;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stuff")
	float WidthOfDoor = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stuff")
	float HeightOfDoor = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door Stuff")
	float DepthOfDoor = 25;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& xform) override;

	virtual void Interact();
};
