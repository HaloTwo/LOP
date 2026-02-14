// Fill out your copyright notice in the Description page of Project Settings.

#include "LOP_GameInstance.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StreamableManager.h" 
#include "Engine/AssetManager.h"        

TSoftObjectPtr<UWorld> ULOP_GameInstance::GetGameLevelByTag(FGameplayTag InTag) const
{
	for (const FGameLevelSet& GameLevelSet : GameLevelSets)
	{
		if (!GameLevelSet.IsValid()) continue;

		if (GameLevelSet.LevelTag == InTag)
		{
			return GameLevelSet.Level;
		}
	}

	return TSoftObjectPtr<UWorld>();
}

void ULOP_GameInstance::BeginAsyncLoadLevel(FGameplayTag InTag)
{
	TSoftObjectPtr<UWorld> LevelToLoad = GetGameLevelByTag(InTag);
	if (LevelToLoad.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("[GameInstance] Invalid Level for Tag: %s"), *InTag.ToString());
		return;
	}

	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	CurrentLevelHandle = Streamable.RequestAsyncLoad(
		LevelToLoad.ToSoftObjectPath(),
		FStreamableDelegate::CreateUObject(this, &ULOP_GameInstance::OnLevelLoaded)
	);

	UE_LOG(LogTemp, Log, TEXT("[GameInstance] Start AsyncLoad for %s"), *LevelToLoad.ToString());
}

void ULOP_GameInstance::OnLevelLoaded()
{
	if (!CurrentLevelHandle.IsValid())
		return;

	UObject* LoadedObj = CurrentLevelHandle->GetLoadedAsset();
	UWorld* LoadedWorld = Cast<UWorld>(LoadedObj);

	if (LoadedWorld)
	{
		PendingLevel = LoadedWorld; // 저장만 해둠
		UE_LOG(LogTemp, Log, TEXT("[GameInstance] AsyncLoad Complete: %s (waiting for commit)"), *LoadedWorld->GetName());
	}
}

void ULOP_GameInstance::CommitLoadedLevel()
{
	if (PendingLevel.IsNull())
	{
		UE_LOG(LogTemp, Warning, TEXT("[GameInstance] No pending level to open."));
		return;
	}

	FName LevelName = FName(*PendingLevel.GetAssetName());
	UGameplayStatics::OpenLevel(this, LevelName);

	// 다 썼으니 초기화
	PendingLevel = nullptr;
	CurrentLevelHandle.Reset();
}

float ULOP_GameInstance::GetAsyncLoadProgress() const
{
	if (CurrentLevelHandle.IsValid())
	{
		return CurrentLevelHandle->GetProgress(); // 0.0 ~ 1.0
	}
	return 0.f;
}




