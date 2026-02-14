// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

class ULOP_WidgetBase;
/**
 * 
 */
UCLASS()
class LISEOFP_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(ULOP_WidgetBase* InWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();

private:
	TArray<ULOP_WidgetBase*> EnemyDrawnWidgets;
};
