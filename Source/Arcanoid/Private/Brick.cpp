// Fill out your copyright notice in the Description page of Project Settings.


#include "Brick.h"
#include "Kismet/KismetMathLibrary.h"
#include "ArcanoidPawn.h"


// Sets default values
ABrick::ABrick()
{
	HitsToDestroy = 1;
	PickupSpawnProbability = 1.0f;
}

// Called when the game starts or when spawned
void ABrick::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABrick::TrySpawnPickUp()
{
	if (PickupsType.Num() == 0)  return;
	auto TestProbability = UKismetMathLibrary::RandomFloat();
	if(PickupSpawnProbability > TestProbability)
	{
		auto RandomPickup = UKismetMathLibrary::RandomIntegerInRange(0, PickupsType.Num() - 1);

		FActorSpawnParameters SpawnParams;	
		SpawnParams.Instigator = GetInstigator();
		SpawnParams.Owner = this;
		//Not the best way to bind Brick with PlayerPawn but it works.
		//If something needed to be done fast it can be done this way
		auto Pawn = Cast<AArcanoidPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(),0));
		auto NewLocation = GetActorLocation();
		auto NewRotation = UKismetMathLibrary::MakeRotFromZX(FVector(0.0f, 0.0f, 1.0f), (Pawn->Platform->GetComponentLocation() - NewLocation));
		auto PickupActor = GetWorld()->SpawnActor<APickUp>(PickupsType[RandomPickup], NewLocation, NewRotation, SpawnParams);
	}
}

void ABrick::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved,
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	HitsToDestroy--;
	if(HitsToDestroy <= 0)
	{
		TrySpawnPickUp();
		Destroy();
	}
}
