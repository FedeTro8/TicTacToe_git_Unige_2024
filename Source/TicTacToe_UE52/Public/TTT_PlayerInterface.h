// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TTT_PlayerInterface.generated.h"

UENUM() //enumerativo per segnalare preso da X , da O oppure empty 
enum class ESign : uint8
{
	X,
	O,
	E
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTTT_PlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TICTACTOE_UE52_API ITTT_PlayerInterface //interfaccia comune per ogni tipo di classe derivata
{												//notare che inizia per I e non per U essendo un interface e non un Uobject 
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	int32 PlayerNumber;
	ESign Sign;

	virtual void OnTurn() {};
	virtual void OnWin() {};
	virtual void OnLose() {};
};
