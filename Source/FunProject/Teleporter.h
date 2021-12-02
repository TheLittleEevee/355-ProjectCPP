// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "UObject/ConstructorHelpers.h"
#include "InteractableThing.h"

#include "Teleporter.generated.h"

UCLASS()
class FUNPROJECT_API ATeleporter : public AActor, public IInteractableThing
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();

	//scene component for root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* TheRoot;

	//scene component for the destination
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* DestinationRoot;

	//mesh for teleporter pad
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* TheDestination;

	//mesh for destination
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UInstancedStaticMeshComponent* TeleporterPad;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleporter Stuff")
	float WidthOfPad = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleporter Stuff")
	float HeightOfPad = 80;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleporter Stuff")
	float DepthOfPad = 200;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& xform) override;

	virtual void Interact();

};
