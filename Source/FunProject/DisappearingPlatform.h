// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "UObject/ConstructorHelpers.h"

#include "DisappearingPlatform.generated.h"

UCLASS()
class FUNPROJECT_API ADisappearingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADisappearingPlatform();

	//scene component for root
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* TheRoot;

	//mesh for platform
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* ThePlatform;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Stuff")
	class UMaterial* NormalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Stuff")
	class UMaterial* InvisMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Stuff")
	float changeTimer = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Stuff")
	bool startNormal = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Stuff")
	float WidthOfPlat = 200;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Stuff")
	float HeightOfPlat = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Stuff")
	float DepthOfPlat = 200;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	float counter = 0;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnConstruction(const FTransform& xform) override;

};
