// Fill out your copyright notice in the Description page of Project Settings.


#include "Dummy/DummyActor.h"
#include "LOP_FunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/SkeletalMesh.h"  // USkeletalMesh, FSkeletalMaterial
#include "Engine/SkinnedAssetCommon.h"  //  FSkeletalMaterial 정의 여기 있음
#include "Items/Weapons/WeaponBase.h"

#include "Components/UI/PlayerUIComponent.h"
#include "Characters/PlayerCharacter.h"




ADummyActor::ADummyActor()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	HeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadMesh"));
	HeadMesh->SetupAttachment(Mesh);
	HeadMesh->SetLeaderPoseComponent(Mesh);

	HairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMesh"));
	HairMesh->SetupAttachment(Mesh);
	HairMesh->SetLeaderPoseComponent(Mesh);

	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmsMesh"));
	ArmsMesh->SetupAttachment(Mesh);
	ArmsMesh->SetLeaderPoseComponent(Mesh);

}


void ADummyActor::BeginPlay()
{
	Super::BeginPlay();

	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
	if (Player)
	{

		Player->GetPlayerUIComponent()->PreviewDummy = this;
		Player->GetInventoryComponentComponent()->PreviewDummy = this;
		TargetPlayer = Player;
	}
}



// 처음 킬 때
void ADummyActor::CopyAppearanceFrom()
{
	if (!TargetPlayer) return;

	// 바디 메쉬
	if (TargetPlayer->GetMesh() && TargetPlayer->GetMesh()->GetSkeletalMeshAsset())
	{
		Mesh->SetSkeletalMesh(TargetPlayer->GetMesh()->GetSkeletalMeshAsset());
		for (int32 i = 0; i < TargetPlayer->GetMesh()->GetNumMaterials(); i++)
		{
			Mesh->SetMaterial(i, TargetPlayer->GetMesh()->GetMaterial(i));
		}
	}


	//헤드 메쉬
	if (TargetPlayer->HeadMesh && TargetPlayer->HeadMesh->GetSkeletalMeshAsset())
	{
		HeadMesh->SetSkeletalMesh(TargetPlayer->HeadMesh->GetSkeletalMeshAsset());
		for (int32 i = 0; i < TargetPlayer->HeadMesh->GetNumMaterials(); i++)
		{
			HeadMesh->SetMaterial(i, TargetPlayer->HeadMesh->GetMaterial(i));
		}
	}

	// 헤어 메쉬
	if (TargetPlayer->HairMesh && TargetPlayer->HairMesh->GetSkeletalMeshAsset())
	{
		HairMesh->SetSkeletalMesh(TargetPlayer->HairMesh->GetSkeletalMeshAsset());
		for (int32 i = 0; i < TargetPlayer->HairMesh->GetNumMaterials(); i++)
		{
			HairMesh->SetMaterial(i, TargetPlayer->HairMesh->GetMaterial(i));
		}
	}

	// 팔 메쉬
	//if (TargetPlayer->ArmsMesh && TargetPlayer->ArmsMesh->GetSkeletalMeshAsset())
	//{
	//	ArmsMesh->SetSkeletalMesh(TargetPlayer->ArmsMesh->GetSkeletalMeshAsset());
	//	for (int32 i = 0; i < TargetPlayer->ArmsMesh->GetNumMaterials(); i++)
	//	{
	//		ArmsMesh->SetMaterial(i, TargetPlayer->ArmsMesh->GetMaterial(i));
	//	}
	//}
}

void ADummyActor::ApplyAppearanceTo(class UClass* AnimBP)
{
	if (!TargetPlayer) return;

	if (Mesh && Mesh->GetSkeletalMeshAsset())
	{
		TargetPlayer->GetMesh()->SetSkeletalMesh(Mesh->GetSkeletalMeshAsset());
		TargetPlayer->GetMesh()->EmptyOverrideMaterials();
		TargetPlayer->GetMesh()->LinkAnimClassLayers(AnimBP);
	}

	if (HairMesh && HairMesh->GetSkeletalMeshAsset())
	{
		TargetPlayer->HairMesh->SetSkeletalMesh(HairMesh->GetSkeletalMeshAsset());
		TargetPlayer->HairMesh->EmptyOverrideMaterials();

	}
}

void ADummyActor::ApplyItemMesh(EItemType ItemType, USkeletalMesh* USkeletalMesh, class UClass* AnimBP)
{
	if (!USkeletalMesh)
	{
		UE_LOG(LogTemp, Error, TEXT("[DummyActor] No mesh to apply for type %d"), (int32)ItemType);
		return;
	}

	USkeletalMeshComponent* TargetComp = nullptr;
	switch (ItemType)
	{
	case EItemType::Clothes: TargetComp = Mesh; break;
	case EItemType::Helmet:  TargetComp = HairMesh; break;
	default: return;
	}

	TargetComp->SetSkeletalMesh(USkeletalMesh, true);
	TargetComp->EmptyOverrideMaterials(); // 메쉬 기본 머티리얼로 초기화

	ApplyAppearanceTo(AnimBP);
}


void ADummyActor::EquipDummyWeapon(UDataAsset_PlayerWeaponDatas* WeaponData)
{
	if (!WeaponData || !Mesh) return;

	UWorld* World = GetWorld();
	if (!World) return;

	// 이미 있던 무기 제거
	if (DummyWeapon)
	{
		DummyWeapon->Destroy();
		DummyWeapon = nullptr;
	}

	// 새 무기 스폰
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;

	DummyWeapon = World->SpawnActor<AWeaponBase>(WeaponData->WeaponClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);

	if (DummyWeapon)
	{
		// 메쉬 소켓에 붙이기
		DummyWeapon->AttachToComponent(Mesh, FAttachmentTransformRules::SnapToTargetIncludingScale, TEXT("BN_Weapon_R")); // 무기용 소켓 이름);

		// AnimLayer도 적용 가능
		switch (WeaponData->WeaponType)
		{
		case EWeaponType::OneHand:
			Mesh->PlayAnimation(OneHandAnim, true); // true = 루프
			break;

		case EWeaponType::TwoHand:
			Mesh->PlayAnimation(TwoHandAnim, true);
			break;

		default:
			UE_LOG(LogTemp, Warning, TEXT("[Dummy] WeaponType not handled"));
			break;
		};

	}
}
