// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/InteractableBase.h"
#include "Components/SphereComponent.h"
#include "Characters/PlayerCharacter.h"
#include "AbilitySystem/LOP_AbilitySystemComponent.h"

// Sets default values
AInteractableBase::AInteractableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractionCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionCollisionSphere"));
	SetRootComponent(InteractionCollisionSphere);
	InteractionCollisionSphere->InitSphereRadius(50.f);
	InteractionCollisionSphere->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnInteractableCollsionSphereBeginOverlap);
}

void AInteractableBase::ExecuteInteract(APlayerCharacter* playerCharacter)
{
	BP_ExecuteInteract(playerCharacter);
}


void AInteractableBase::OnInteractableCollsionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


}


