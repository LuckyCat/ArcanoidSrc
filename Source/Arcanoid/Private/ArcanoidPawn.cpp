// Fill out your copyright notice in the Description page of Project Settings.


#include "ArcanoidPawn.h"
#include "PickUp.h"

// Sets default values
AArcanoidPawn::AArcanoidPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WorldBorder = CreateDefaultSubobject<USphereComponent>("WorldBorders");
	WorldBorder->SetGenerateOverlapEvents(true);
	SetRootComponent(WorldBorder);

	SplineRails = CreateDefaultSubobject<USplineComponent>(TEXT("SplineRails"));
	SplineRails->SetupAttachment(RootComponent);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("ArcanoidCamera"));
	Camera->SetupAttachment(SpringArm);
	Camera->FieldOfView = 95.0f;

	Platform = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform"));
	Platform->SetupAttachment(SplineRails);

	BallSpawnLocation = CreateDefaultSubobject<USphereComponent>("BallSpawnLocation");
	BallSpawnLocation->SetupAttachment(Platform);

	CurrentRotation = 0.5f;
	Lives = 3;
}

// Called when the game starts or when spawned
void AArcanoidPawn::BeginPlay()
{
	Super::BeginPlay();
	WorldBorder->OnComponentEndOverlap.AddDynamic(this, &AArcanoidPawn::OnWorldBorderOverlapEnd);
	Platform->OnComponentBeginOverlap.AddDynamic(this, &AArcanoidPawn::OnPlatformOverlapBegin);
	Respawn();
}

void AArcanoidPawn::OnWorldBorderOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	auto Ball = Cast<ABall>(OtherActor);
	if (Ball) 
	{
		Balls.Remove(Ball);
		Ball->Destroy();
		if(Balls.Num() == 0)
		{
			Lives--;
			if(Lives)
			{
				Respawn();
			}else
			{
				GameOver();
			}
		}
		return;
	}
	auto PickUp = Cast<APickUp>(OtherActor);
	if (PickUp)
	{
		PickUp->Destroy();
	}
}

void AArcanoidPawn::OnPlatformOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int OtherBodyIndex, bool bFromSweep, const FHitResult& HitResult)
{
	auto PickUp = Cast<APickUp>(OtherActor);
	if (PickUp)
	{
		PickUp->UsePickUp(this);
	}
}


// Called every frame
void AArcanoidPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	RefreshPawnLocation();
}

void AArcanoidPawn::RefreshPawnLocation()
{
	Platform->SetWorldLocationAndRotation(
		SplineRails->GetLocationAtSplineInputKey(CurrentLocation, ESplineCoordinateSpace::World),
		FRotator(0.0f,CurrentRotation * -180.0f, 0.0f)
	);
}

void AArcanoidPawn::Fire()
{
	// I use lambda here because I can! :-)
	ForEachAttachedActors(
		[&](AActor* Actor)
		{
			auto Ball = Cast<ABall>(Actor);
			if(Ball)
			{
				Ball->WakeUp();
			}
			return true;
		}
	);
}

void AArcanoidPawn::Respawn()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Instigator = GetInstigator();
	SpawnParams.Owner = this;
	auto NewLocation= BallSpawnLocation->GetComponentLocation();
	auto NewRotation = BallSpawnLocation->GetComponentRotation();
	auto NewBall = GetWorld()->SpawnActor<ABall>(BallClass, NewLocation, NewRotation, SpawnParams);
	NewBall->AttachToComponent(BallSpawnLocation, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Balls.AddUnique(NewBall);
}
