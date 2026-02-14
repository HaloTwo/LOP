// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractableBase.generated.h"

class USphereComponent;
class ULOP_AbilitySystemComponent;
class UGameplayEffect;
class APlayerCharacter;

UCLASS()
class LISEOFP_API AInteractableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableBase();

	void ExecuteInteract(APlayerCharacter* playerCharacter);
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	USphereComponent* InteractionCollisionSphere;

	// 겹침 시작 시 (E 버튼 UI 띄우기)
	UFUNCTION()
	virtual void OnInteractableCollsionSphereBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//실행하면 나오는 이벤트
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnInteraction"))
	void BP_ExecuteInteract(APlayerCharacter* playerCharacter);
};
