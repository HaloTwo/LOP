// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item_Interactable.h"
#include "Characters/PlayerCharacter.h"
#include "AbilitySystem/LOP_AbilitySystemComponent.h"
#include "LOP_GameplayTags.h"

void AItem_Interactable::OnInteractableCollsionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (APlayerCharacter* OverlappedHeroCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		OverlappedHeroCharacter->GetBaseAbilitySystemComponent()->TryActivateAbilityByTag(LOP_GameplayTags::Player_Ability_Interractable_Item);
	}
}