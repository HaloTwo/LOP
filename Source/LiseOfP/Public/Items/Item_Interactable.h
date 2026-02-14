// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/InteractableBase.h"
#include "Item_Interactable.generated.h"

/**
 * 
 */
UCLASS()
class LISEOFP_API AItem_Interactable : public AInteractableBase
{
	GENERATED_BODY()
	
protected:
	virtual void OnInteractableCollsionSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
