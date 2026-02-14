// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/StreamableManager.h"  
#include "GameplayTagContainer.h"
#include "LOP_GameInstance.generated.h"

USTRUCT(BlueprintType)
struct FGameLevelSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "GameData.Level"))
	FGameplayTag LevelTag;

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Level;

	bool IsValid() const
	{
		return LevelTag.IsValid() && !Level.IsNull();
	}
};


/**
 * 
 */
UCLASS()
class LISEOFP_API ULOP_GameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FGameLevelSet> GameLevelSets;

	//Async 핸들
	TSharedPtr<FStreamableHandle> CurrentLevelHandle;

	//로드 끝난 에셋 저장
	TSoftObjectPtr<UWorld> PendingLevel;

	//로드 완료 콜백
	void OnLevelLoaded();

public:
	//태그로 레벨 찾기
	UFUNCTION(BlueprintCallable, meta = (GameplayTagFilter = "GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(FGameplayTag InTag) const;

	//비동기 레벨 로드 시작
	UFUNCTION(BlueprintCallable)
	void BeginAsyncLoadLevel(FGameplayTag InTag);

	//로딩된 레벨로 전환
	UFUNCTION(BlueprintCallable)
	void CommitLoadedLevel(); 

	//비동기 로드 진행률 반환 (0.0 ~ 1.0)
	UFUNCTION(BlueprintCallable)
	float GetAsyncLoadProgress() const;
};

