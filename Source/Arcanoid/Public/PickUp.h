// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "ArcanoidPawn.h"
#include "PickUp.generated.h"

UCLASS()
class ARCANOID_API APickUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUp();

protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;

public:	
	// Called every frame
	void Tick(float DeltaTime) override;

	UPROPERTY(Category = "Properties", VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* SphereCollider;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void MovePickUp(float DeltaSeconds);

	void UsePickUp(AArcanoidPawn* PlayerPawn);

	UPROPERTY(Category = "Properties", EditAnywhere, BlueprintReadWrite)
		float Speed;

	UFUNCTION(BlueprintImplementableEvent)
		void OnPickedByPlayer(AArcanoidPawn* Pawn);
};
