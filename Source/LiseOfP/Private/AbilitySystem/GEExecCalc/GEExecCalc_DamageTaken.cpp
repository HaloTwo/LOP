// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"

#include "AbilitySystem/LOP_AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "LOP_GameplayTags.h"

#include "LOP_DebugHelper.h"


struct DamageCaptureDef
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken)

	DamageCaptureDef()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(ULOP_AttributeSet, DamageTaken, Source, false);
	}
};

static const DamageCaptureDef& GetDamageCapture()
{
	static DamageCaptureDef DamageCapture;
	return DamageCapture;
}




UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	// 능력치 캡처 정의
	RelevantAttributesToCapture.Add(GetDamageCapture().DamageTakenDef);
}


void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvalParams;
	EvalParams.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvalParams.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	//SetByCaller 값 추출
	const float BaseDamage = EffectSpec.GetSetByCallerMagnitude(LOP_GameplayTags::Shared_SetByCaller_BaseDamage, false, 0.f);
	const int32 LightAttackComboCount = (int32)EffectSpec.GetSetByCallerMagnitude(LOP_GameplayTags::Player_SetByCaller_AttackType_Light, false, 0.f);
	const int32 HeavyAttackComboCount = (int32)EffectSpec.GetSetByCallerMagnitude(LOP_GameplayTags::Player_SetByCaller_AttackType_Heavy, false, 0.f);

	//최종 데미지 계산
	float FinalDamage = BaseDamage;

	//콤보 보정
	if (LightAttackComboCount > 0)
	{
		FinalDamage *= 1.0f + (LightAttackComboCount * 0.05f);
	}
	if (HeavyAttackComboCount > 0)
	{
		FinalDamage *= 1.0f + (HeavyAttackComboCount * 0.1f);
	}

	const float RandomOffset = FMath::RandRange(-3.f, 3.f);
	FinalDamage += RandomOffset;

	FinalDamage = FMath::Max(FinalDamage, 1.0f);
	FinalDamage = FMath::RoundToFloat(FinalDamage);

	//Debug::Print(TEXT("FinalDamageDone"), FinalDamage);

	//결과 반영
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(ULOP_AttributeSet::GetDamageTakenAttribute(), EGameplayModOp::Override, FinalDamage));
}


