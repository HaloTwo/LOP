// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PawnCombatComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"   
#include "Items/Weapons/WeaponBase.h"
#include "Components/BoxComponent.h"

//무기	태그를 사용하여 캐릭터가 소지한 무기를 등록합니다.
void UPawnCombatComponent::RegisterSpawnedWeapon(AWeaponBase* InWeaponToRegister, UDataAsset_WeaponDatas* WeaponData, bool bRegisterAsEquippedWeapon)
{
    if (bRegisterAsEquippedWeapon)
    {
        InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnHitTargetActor);
        //InWeaponToRegister->OnWeaponPulledFromTarget.BindUObject(this, &ThisClass::OnWeaponPulledFromTargetActor);
        InWeaponToRegister->OnWeaponHitBlocking.BindUObject(this, &ThisClass::OnHitBlocking);

        EquippedWeapon = InWeaponToRegister;
        WeaponDataAsset = WeaponData;
    }

    UE_LOG(LogTemp, Warning, TEXT("Registered weapon: %s"), *InWeaponToRegister->GetName());
}

void UPawnCombatComponent::ToggleWeaponCollision(ECollsionToggle bEnableCollision, EToggleDamageType ToggleDamageType)
{
    if (ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
    {
        if (EquippedWeapon)
        {
            switch (bEnableCollision)
            {

            case ECollsionToggle::Start:
				EquippedWeapon->StartWeaponTrace();
                break;

            case ECollsionToggle::Tick:
                EquippedWeapon->PerformWeaponTrace();
                break;

            case ECollsionToggle::End:
                EquippedWeapon->StopWeaponTrace();
                OverlappedActors.Empty();       
                break;

            }
        }
    }
}

void UPawnCombatComponent::ToggleBodyCollision(ECollsionToggle bShouldEnable, EToggleDamageType ToggleDamageType)
{


}



void UPawnCombatComponent::OnHitTargetActor(AActor* HitActor, FVector ImpactPoint)
{

}

//void UPawnCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
//{
//   
//}

void UPawnCombatComponent::OnHitBlocking(AActor* HitActor, FVector vector, EPhysicalSurface SurfaceType)
{
   
}
