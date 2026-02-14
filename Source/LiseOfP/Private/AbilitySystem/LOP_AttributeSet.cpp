// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/LOP_AttributeSet.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameplayEffectExtension.h"

#include "LOP_FunctionLibrary.h"
#include "LOP_GameplayTags.h"

#include "Interfaces/PawnUIInterface.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/PlayerUIComponent.h"

#include "LOP_DebugHelper.h"

ULOP_AttributeSet::ULOP_AttributeSet()
{
	// 'P의 거짓' 기반 스탯 초기화
	InitMaxHealth(1.f);    // 체력 영향 스탯
	InitCurrentHealth(1.f);
	InitMaxStamina(1.f);    //스태미나 영향 스탯
	InitCurrentStamina(1.f);

	InitCapacity(1.f);    // 적재력 영향 스탯

	InitMotivity(1.f);    // 동력 / 힘 계열 무기 보정 스탯
	InitTechnique(1.f);   // 기술 / 민첩 계열 무기 보정 스탯
	InitAdvance(1.f);     // 진화 / 속성, 상태이상 계열 보정 스탯
}

void ULOP_AttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

	checkf(PawnUIComponent, TEXT("Couldn't extract a PawnUIComponent from %s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());



	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

		// 현재 체력을 최대 체력으로 제한
		SetCurrentHealth(NewCurrentHealth);

		//CurrentHealthChanged 이벤트를 호출하여 UI에 알림
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth(), 0);
	}

	if (Data.EvaluatedData.Attribute == GetCurrentStaminaAttribute())
	{
		const float NewCurrentStamina = FMath::Clamp(GetCurrentStamina(), 0.f, GetMaxStamina());

		SetCurrentStamina(NewCurrentStamina);

		//CurrentStaminaChanged 이벤트를 호출하여 UI에 알림
		if (UPlayerUIComponent* PlayerUIComponent = CachedPawnUIInterface->GetPlayerUIComponent())
		{
			// 현재 스태미나가 변경되었음을 UI에 알림
			PlayerUIComponent->OnCurrentStaminaChanged.Broadcast(GetCurrentStamina() / GetMaxStamina(), 0);
		}
	}

	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		//CurrentHealthChanged 이벤트를 호출하여 UI에 알림
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth(), DamageDone);


		if (APawn* Pawn = Cast<APawn>(Data.Target.GetAvatarActor()))
		{
			if (AAIController* AIC = Cast<AAIController>(Pawn->GetController()))
			{
				const float Pct = (GetMaxHealth() > 0.f) ? (GetCurrentHealth() / GetMaxHealth()) : 0.f;

				if (Pct <= 0.6f)
				{
					if (UBlackboardComponent* BB = AIC->GetBlackboardComponent())
					{
						if (!BB->GetValueAsBool(TEXT("Phase2Ready")))
						{
							BB->SetValueAsBool(TEXT("Phase2Ready"), true);
						}
					}
				}
			}
		}


		//TODO::Handle character death
		if (GetCurrentHealth() == 0.f)
		{
			//죽음 상태로 변경
			ULOP_FunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), LOP_GameplayTags::Shared_Status_Dead);
		}
	}

}
