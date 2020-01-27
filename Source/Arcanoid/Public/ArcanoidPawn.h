// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SplineComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Ball.h"

#include "ArcanoidPawn.generated.h"

UCLASS()
class ARCANOID_API AArcanoidPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AArcanoidPawn();


	UPROPERTY(Category = "Properties", VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* WorldBorder;
	
	UPROPERTY(Category = "Properties", VisibleAnywhere, BlueprintReadOnly)
		UStaticMeshComponent* Platform;

	UPROPERTY(Category = "Properties", VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* BallSpawnLocation;
	
	UPROPERTY(Category = "Properties", VisibleAnywhere, BlueprintReadOnly)
		USplineComponent* SplineRails;

	UPROPERTY(Category = "Properties", VisibleAnywhere, BlueprintReadOnly)
		USpringArmComponent* SpringArm;

	UPROPERTY(Category = "Properties", VisibleAnywhere, BlueprintReadOnly)
		UCameraComponent* Camera;


	UPROPERTY(Category = "Properties", EditAnywhere, BlueprintReadWrite)
		float CurrentLocation;

	UPROPERTY(Category = "Properties", EditAnywhere, BlueprintReadWrite)
		float CurrentRotation;
	
	UPROPERTY(Category = "Properties", EditAnywhere, BlueprintReadWrite)
		TSubclassOf<ABall> BallClass;
	
	UPROPERTY(Category = "Properties", EditAnywhere, BlueprintReadWrite)
		TArray<ABall*> Balls;	


	UPROPERTY(Category = "Properties", EditAnywhere, BlueprintReadWrite)
		int Lives;
	
	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnWorldBorderOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void OnPlatformOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult);

	UFUNCTION(BlueprintImplementableEvent)
		void GameOver();

	UFUNCTION(BlueprintCallable)
		void RefreshPawnLocation();
	
	UFUNCTION(BlueprintCallable)
		void Fire();

	UFUNCTION(BlueprintCallable)
		void Respawn();
};
