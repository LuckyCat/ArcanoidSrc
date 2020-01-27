// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Arcanoid/Arcanoid.h"

#include "Ball.generated.h"

UCLASS()
class ARCANOID_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	

	ABall();

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

	void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	
	UPROPERTY(Category = "Properties", VisibleAnywhere, BlueprintReadOnly)
		USphereComponent* SphereCollider;
	
	UPROPERTY(Category = "Properties", EditAnywhere, BlueprintReadWrite)
		float Speed;
	
	UFUNCTION(BlueprintCallable, Category = "Movement")
		void MoveBall(float DeltaSeconds);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void ChangeDirection(FVector HitNormal);

	UFUNCTION(BlueprintCallable, Category = "Movement")
		void WakeUp();
};
