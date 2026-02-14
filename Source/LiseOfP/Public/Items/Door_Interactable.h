// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/InteractableBase.h"
#include "LevelSequence.h" // 
#include "Door_Interactable.generated.h"

/**
 * 
 */
UCLASS()
class LISEOFP_API ADoor_Interactable : public AInteractableBase
{
	GENERATED_BODY()
	
public:
	// 에디터에서 드래그해서 세팅할 수 있게 UPROPERTY
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cinematic")
	ULevelSequence* DoorSequence;

protected:
	virtual void OnInteractableCollsionSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
