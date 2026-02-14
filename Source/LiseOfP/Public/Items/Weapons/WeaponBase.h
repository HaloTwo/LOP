#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

class UBoxComponent;
class UParticleSystem;

DECLARE_DELEGATE_TwoParams(FOnTargetInteractedDelegate, AActor*, FVector);
DECLARE_DELEGATE_ThreeParams(FOnWeaponHitBlocking, AActor*, FVector, EPhysicalSurface);


UCLASS()
class LISEOFP_API AWeaponBase : public AActor
{
	GENERATED_BODY()

public:
	AWeaponBase();


	FOnTargetInteractedDelegate OnWeaponHitTarget;
	FOnWeaponHitBlocking OnWeaponHitBlocking;
	//FOnWeaponExitDelegate OnWeaponPulledFromTarget;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StartWeaponTrace();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void PerformWeaponTrace();

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void StopWeaponTrace();


	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons")
	UBoxComponent* WeaponCollisionBox;

private:
	FVector LastLocation;

};
