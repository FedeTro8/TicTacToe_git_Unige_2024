// Fill out your copyright notice in the Description page of Project Settings.


#include "TTT_HumanPlayer.h"
#include "GameField.h"
#include "TTT_GameMode.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

// Sets default values
ATTT_HumanPlayer::ATTT_HumanPlayer()
{
	PrimaryActorTick.bCanEverTick = true;  //ci serve per updatare il nostro stato
	// Set this pawn to be controlled by the lowest-numbered player
	AutoPossessPlayer = EAutoReceiveInput::Player0; //solitamente i player umani sono player 0 
	// create a camera component
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//set the camera as RootComponent
	SetRootComponent(Camera);
	// get the game instance reference
	GameInstance = Cast<UTTT_GameInstance>(UGameplayStatics::GetGameInstance(GetWorld())); //la classe gameplay statics mi permette di creare funzioni statiche per la gameistance 
	// default init values
	PlayerNumber = -1;
	Sign = ESign::E;

}

// Called when the game starts or when spawned
void ATTT_HumanPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATTT_HumanPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATTT_HumanPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATTT_HumanPlayer::OnTurn()
{
	IsMyTurn = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Your Turn")); //DA USARE SOLAMENTE IN DEBUG, non è la ui 8 (che è quella sotto) 
	GameInstance->SetTurnMessage(TEXT("Human Turn"));
}

void ATTT_HumanPlayer::OnWin()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Win!"));
	GameInstance->SetTurnMessage(TEXT("Human Wins!"));
	GameInstance->IncrementScoreHumanPlayer();
}

void ATTT_HumanPlayer::OnLose()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("You Lose!"));
	GameInstance->SetTurnMessage(TEXT("Human Loses!"));
}

void ATTT_HumanPlayer::OnClick()
{
	//Structure containing information about one hit of a trace, such as point of impact and surface normal at that point
	FHitResult Hit = FHitResult(ForceInit);	

	// GetHitResultUnderCursor function sends a ray from the mouse position and gives the corresponding hit results
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Pawn, true, Hit);
	if (Hit.bBlockingHit && IsMyTurn) //devo cliccare sulla cella e deve essere 
	{
		if (ATile* CurrTile = Cast<ATile>(Hit.GetActor()))
		{
			if (CurrTile->GetTileStatus() == ETileStatus::EMPTY) //se la casella è vuota 
			{
				// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("clicked"));
				CurrTile->SetTileStatus(PlayerNumber, ETileStatus::OCCUPIED);
				FVector SpawnPosition = CurrTile->GetActorLocation();  //prende la posizione dello spazio della cella selezionata
				ATTT_GameMode* GameMode = Cast<ATTT_GameMode>(GetWorld()->GetAuthGameMode());
				GameMode->SetCellSign(PlayerNumber, SpawnPosition); //mette il segno giusto
				IsMyTurn = false;
			}
		}
	}
	
	
	
}

