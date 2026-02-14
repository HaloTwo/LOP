// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/BaseAnimInstance.h"
#include "LOP_FunctionLibrary.h"

bool UBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return ULOP_FunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}

	return false;
}
