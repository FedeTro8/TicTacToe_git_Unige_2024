// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; //a false perchè non ne abbiamo bisogno

	// template function that creates a components
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));                                   //servono per aggingerle con una forma nella scena 
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	// every actor has a RootComponent that defines the transform in the World
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene); //attacco il static mesh alla scene

	Status = ETileStatus::EMPTY; //per defualt la casella è vuota
	PlayerOwner = -1;            //per defualt non appartiene ne al player ne all' ia (contrassegnati con 0 e 1)
	TileGridPosition = FVector2D(0, 0);

}

void ATile::SetTileStatus(const int32 TileOwner, const ETileStatus TileStatus)
{
	PlayerOwner = TileOwner;
	Status = TileStatus;
}

ETileStatus ATile::GetTileStatus()
{
	return Status;
}

int32 ATile::GetOwner()
{
	return PlayerOwner;
}

void ATile::SetGridPosition(const double InX, const double InY)
{
	TileGridPosition.Set(InX, InY); //ricordo che è un vettore
}

FVector2D ATile::GetGridPosition()
{
	return TileGridPosition;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
//void ATile::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

