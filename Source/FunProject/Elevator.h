// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "UObject/ConstructorHelpers.h"
#include "InteractableThing.h"

#include "Elevator.generated.h"

UCLASS()
class FUNPROJECT_API AElevator : public AActor, public IInteractableThing
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();

	//scene component for root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* TheRoot;

	//scene component for moving parts
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* MovingRoot;

	//mesh for floor
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* TheFloor;

	//mesh for elevator frame
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UInstancedStaticMeshComponent* TheFrame;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator Stuff")
	float WidthOfElevator = 300;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator Stuff")
	float HeightOfElevator = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator Stuff")
	float DepthOfElevator = 300;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Elevator Stuff")
	FVector CurrentLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Elevator Stuff")
	float speed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& xform) override;

	virtual void Interact();

};
