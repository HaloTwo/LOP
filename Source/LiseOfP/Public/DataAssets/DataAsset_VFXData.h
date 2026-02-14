// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PhysicalMaterials/PhysicalMaterial.h" 
#include "NiagaraSystem.h"                     
#include "DataAsset_VFXData.generated.h"

/**
 * 
 */
UCLASS()
class LISEOFP_API UDataAsset_VFXData : public UDataAsset
{
	GENERATED_BODY()
	

public:
	// 표면 타입별 VFX 매핑
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "VFX")
	TMap<TEnumAsByte<EPhysicalSurface>, TObjectPtr<UNiagaraSystem>> SurfaceImpactVFX;
};
