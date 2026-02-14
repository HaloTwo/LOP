#include "Items/Weapons/WeaponBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/StaticMeshActor.h"  

#include "LOP_FunctionLibrary.h"
#include "DrawDebugHelpers.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollisionBox"));
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetBoxExtent(FVector(20.f));
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWeaponBase::StartWeaponTrace()
{
	if (!WeaponCollisionBox) return;

	LastLocation = WeaponCollisionBox->GetComponentLocation(); 
}


void AWeaponBase::PerformWeaponTrace()
{
	if (!WeaponCollisionBox) return;

	FVector CurrentLocation = WeaponCollisionBox->GetComponentLocation();
	FQuat CurrentRotation = WeaponCollisionBox->GetComponentQuat();
	FVector BoxExtent = WeaponCollisionBox->GetScaledBoxExtent();

	FCollisionQueryParams Params(SCENE_QUERY_STAT(WeaponTrace), false, this);
	Params.bReturnPhysicalMaterial = true;

	if (APawn* OwnerPawn = GetInstigator<APawn>())
	{
		Params.AddIgnoredActor(OwnerPawn);
	}
	else if (AActor* OwnerActor = GetOwner())
	{
		Params.AddIgnoredActor(OwnerActor);
	}

	// Debug
	DrawDebugBox(GetWorld(), CurrentLocation, BoxExtent, CurrentRotation, FColor::Green, false, 0.02f);
	DrawDebugLine(GetWorld(), LastLocation, CurrentLocation, FColor::Yellow, false, 0.2f);

	if (!LastLocation.IsNearlyZero())
	{
		TArray<FHitResult> HitResults;
		bool bHit = GetWorld()->SweepMultiByChannel(
			HitResults,
			LastLocation,
			CurrentLocation,
			CurrentRotation,
			ECC_Pawn,
			FCollisionShape::MakeBox(BoxExtent),
			Params
		);

		if (bHit)
		{
			for (const FHitResult& Hit : HitResults)
			{
				AActor* OtherActor = Hit.GetActor();
				if (!OtherActor || OtherActor == GetInstigator()) continue;

				if (APawn* HitPawn = Cast<APawn>(OtherActor))
				{
					if (ULOP_FunctionLibrary::IsTargetPawnHostile(GetInstigator<APawn>(), HitPawn))
					{
						OnWeaponHitTarget.ExecuteIfBound(HitPawn, Hit.ImpactPoint);
					}
				}
				else if (Hit.Component.IsValid() && Hit.Component->GetCollisionObjectType() == ECC_WorldStatic)
				{
					EPhysicalSurface SurfaceType = SurfaceType_Default;
					if (UPhysicalMaterial* PhysMat = Hit.PhysMaterial.Get())
					{
						SurfaceType = UPhysicalMaterial::DetermineSurfaceType(PhysMat);
					}

					OnWeaponHitBlocking.ExecuteIfBound(OtherActor, Hit.ImpactPoint, SurfaceType);
				}
			}
		}
	}

	LastLocation = CurrentLocation;
}

void AWeaponBase::StopWeaponTrace()
{
	LastLocation = FVector::ZeroVector;
}

