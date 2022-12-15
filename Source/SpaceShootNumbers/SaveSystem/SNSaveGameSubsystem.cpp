// Fill out your copyright notice in the Description page of Project Settings.


#include "SNSaveGameSubsystem.h"
#include "SNSaveGame.h"
#include <Kismet/GameplayStatics.h>

void USNSaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USNSaveGameSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void USNSaveGameSubsystem::SaveGame(int32 PlayerScore, int32 PlayTimeInSeconds, int32 UserIndex /*= -1*/)
{
	if (USNSaveGame* SaveGameInstance = Cast<USNSaveGame>(UGameplayStatics::CreateSaveGameObject(USNSaveGame::StaticClass())))
	{
		// Set up the (optional) delegate.
		FAsyncSaveGameToSlotDelegate SavedDelegate;
		// USomeUObjectClass::SaveGameDelegateFunction is a void function that takes the following parameters: const FString& SlotName, const int32 UserIndex, bool bSuccess
		SavedDelegate.BindUObject(this, &USNSaveGameSubsystem::SaveGameFinished);

		SaveGameInstance->PlayerName = TEXT("PlayerOne");
		SaveGameInstance->PlayerScore = PlayerScore;
		SaveGameInstance->PlayTimeInSeconds = PlayTimeInSeconds;

		// Start async save process.
		UGameplayStatics::AsyncSaveGameToSlot(SaveGameInstance, SaveGameInstance->SaveSlotName, UserIndex, SavedDelegate);
	}
}

void USNSaveGameSubsystem::LoadGame()
{
	FAsyncLoadGameFromSlotDelegate LoadedDelegate;
	LoadedDelegate.BindUObject(this, &USNSaveGameSubsystem::LoadGameFinished);
	UGameplayStatics::AsyncLoadGameFromSlot(TEXT("SaveSlot"), 0, LoadedDelegate);
}

void USNSaveGameSubsystem::SaveGameFinished(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("Save game finished: save slot name - %s, User index - %d, bSuccess - %d"), *SlotName, UserIndex, bSuccess);
	OnSaveGameFinished.Broadcast(SlotName, UserIndex, bSuccess);
}

void USNSaveGameSubsystem::LoadGameFinished(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	UE_LOG(LogTemp, Warning, TEXT("Load game finished: save slot name - %s, User index - %d"), *SlotName, UserIndex);

	if (USNSaveGame* LoadedData = Cast<USNSaveGame>(LoadedGameData))
	{
		OnLoadGameFinished.Broadcast(LoadedData);
	}
}
