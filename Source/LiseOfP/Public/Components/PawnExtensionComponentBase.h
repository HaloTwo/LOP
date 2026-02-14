// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PawnExtensionComponentBase.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LISEOFP_API UPawnExtensionComponentBase : public UActorComponent
{
	GENERATED_BODY()

protected:
	//폰 확장 컴포넌트는 Pawn이 소유하는 컴포넌트로, Pawn이 소멸될 때 자동으로 제거됩니다.
	template <class T>
	T* GetOwningPawn() const // T는 APawn 또는 그 파생 클래스여야 합니다.
	{
		static_assert(TPointerIsConvertibleFromTo<T, APawn>::Value, "'T' Template Parameter to GetPawn must be derived from APawn");
		return CastChecked<T>(GetOwner());
	}

	APawn* GetOwningPawn() const // APawn 또는 그 파생 클래스가 아닌 경우에도 사용할 수 있도록 오버로드합니다.
	{
		return GetOwningPawn<APawn>();
	}

	template <class T>
	T* GetOwningController() const //
	{
		static_assert(TPointerIsConvertibleFromTo<T, AController>::Value, "'T' Template Parameter to GetController must be derived from AController");
		return GetOwningPawn<APawn>()->GetController<T>();
	}

		
};
