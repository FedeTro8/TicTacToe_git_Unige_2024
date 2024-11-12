// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tile.h"
#include "GameFramework/Actor.h"
#include "GameField.generated.h"

// macro declaration for a dynamic multicast delegate
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnReset);

UCLASS()
class TICTACTOE_UE52_API AGameField : public AActor
{
	GENERATED_BODY()
	
public:	
	// keeps track of tiles
	UPROPERTY(Transient)
	TArray<ATile*> TileArray;               //array e mappa qua sotto sono modi differenti di tenere traccia dei nostri Tile 

	//given a position returns a tile
	UPROPERTY(Transient)
	TMap<FVector2D, ATile*> TileMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float NextCellPositionMultiplier;     //sapendo la proporzione delle celle, so sempre la loro posizione nello spazio

	static const int32 NOT_ASSIGNED = -1; 

	// BlueprintAssignable Usable with Multicast Delegates only. Exposes the property for assigning in Blueprints.
	// declare a variable of type FOnReset (delegate)
	UPROPERTY(BlueprintAssignable)
		FOnReset OnResetEvent;

	// size of field
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Size;

	// size of winning line
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 WinSize;  //tiene conto del numero di segni per assegnare la vittoria

	// TSubclassOf template class that provides UClass type safety
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ATile> TileClass; //modo che fa dei controlli sul nostro oggetto 

	// tile padding percentage
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float CellPadding;  //serve a mantenere la proporzione tra il bordo e la dimensione della cella 

	// tile size
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float TileSize; //diamo una dimensione predefinita

	// Sets default values for this actor's properties
	AGameField(); //costruttore

	// Called when an instance of this class is placed (in editor) or spawned
	virtual void OnConstruction(const FTransform& Transform) override;  //override metodo di unreal che gestisce il piazzamento o lo spawn

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// remove all signs from the field
	UFUNCTION(BlueprintCallable)
		void ResetField();  

	// generate an empty game field
	void GenerateField();

	// return a (x,y) position given a hit (click) on a field tile
	FVector2D GetPosition(const FHitResult& Hit);   //introduciamo un nuovo tipo, hit result che ritorna la posizione del click del mouse, è come fosse un "raggio" che viene sparato
	//se colpisce determinate cose lancio degli eventi. 

	// return the array of tile pointers
	TArray<ATile*>& GetTileArray();  

	// return a relative position given (x,y) position
	FVector GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const; //dove sta la cella 0 1?

	// return (x,y) position given a relative position
	FVector2D GetXYPositionByRelativeLocation(const FVector& Location) const; //data la posizione, in che cella siamo? 

	// check if a position is a win position
	bool IsWinPosition(const FVector2D Position) const;  //ritorna true se ci sono le condizioni di vittoria

	// check if is a win line
	inline bool IsWinLine(const FVector2D Begin, const FVector2D End) const;

	// checking if is a valid field position
	inline bool IsValidPosition(const FVector2D Position) const; //ritorna se dove ho cliccato è un luogo valido oppure no 

	// get a line given a begin and end positions
	TArray<int32> GetLine(const FVector2D Begin, const FVector2D End) const;  //prendo una riga

	// check if a line contains all equal elements
	bool AllEqual(const TArray<int32>& Array) const;  //presa la riga, verifico se è composta tutta dallo stesso simbolo

//public:	
//	// Called every frame
//	virtual void Tick(float DeltaTime) override;

};
