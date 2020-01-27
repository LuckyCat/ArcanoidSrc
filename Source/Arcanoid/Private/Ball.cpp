// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Kismet/KismetMathLibrary.h"


ABall::ABall()
{
	Speed = 600.0f; // cm per second
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>("SphereCollider");
	SetRootComponent(SphereCollider);

}

void ABall::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickEnabled(false);
}

void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveBall(DeltaTime);
}

void ABall::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	ChangeDirection(Hit.Normal);
}

void ABall::MoveBall(float DeltaSeconds)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * DeltaSeconds * Speed, true);
}

void ABall::ChangeDirection(FVector HitNormal)
{
	SetActorRotation(
			UKismetMathLibrary::MakeRotFromZX(
			FVector(0.0f, 0.0f, 1.0f),
			UKismetMathLibrary::ProjectVectorOnToPlane(
			UKismetMathLibrary::MirrorVectorByNormal(GetActorForwardVector(), HitNormal),
			FVector(0.0f, 0.0f, 1.0f)))
	);
}

void ABall::WakeUp()
{
	SetActorTickEnabled(true);
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}



