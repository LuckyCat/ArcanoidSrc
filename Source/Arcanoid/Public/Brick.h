// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUp.h"
#include "Engine.h"

#include "Brick.generated.h"


UCLASS()
class ARCANOID_API ABrick : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrick();

	void BeginPlay() override;

	UPROPERTY(Category = "Properties", EditAnywhere, BlueprintReadWrite)
		int HitsToDestroy;

	UPROPERTY(Category = "Properties", EditAnywhere, BlueprintReadWrite)
		float PickupSpawnProbability;
	
	UPROPERTY(Category = "Properties", EditAnywhere, BlueprintReadWrite)
		TArray<TSubclassOf<APickUp>> PickupsType;

	void TrySpawnPickUp();

	void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
};
