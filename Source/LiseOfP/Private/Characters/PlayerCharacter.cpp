// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"

#include "DataAssets/DataAsset_InputConfig.h"
#include "DataAssets/StartUpData/DataAsset_PlayerStartUpData.h"

#include "Components//CapsuleComponent.h"
#include "Components/Input/PlayerInputComponent.h"
#include "Components/Inventory/PlayerInventoryComponent.h"
#include "Components/Combat/PlayerCombatComponent.h"
#include "Components/UI/PlayerUIComponent.h"

#include "AbilitySystem/LOP_AbilitySystemComponent.h"  
#include "AbilitySystemBlueprintLibrary.h"

#include "LOP_GameplayTags.h"
#include "LOP_DebugHelper.h"

// 생성자: 컴포넌트 초기화
APlayerCharacter::APlayerCharacter()
{
	// 컨트롤러가 캐릭터를 소유할 때 실행
	// 플레이어 입력 바인딩
	// 게임 시작 시 초기화
	// 이동 입력 처리
	// 카메라 회전 입력 처리
	// 걷기 토글 입력
	// 어빌리티 입력 시작 처리
	// 어빌리티 입력 종료 처리
		// === 메인 바디 (애니메이션 담당) ===
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	// GetMesh()에 바디 스켈레탈 메시와 애니메이션 BP 설정

	// === 추가 부위들 (뼈대만 공유) ===
	HeadMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadMesh"));
	HeadMesh->SetupAttachment(GetMesh());
	HeadMesh->SetMasterPoseComponent(GetMesh());

	HairMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMesh"));
	HairMesh->SetupAttachment(GetMesh());
	HairMesh->SetMasterPoseComponent(GetMesh());

	ArmsMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ArmsMesh"));
	ArmsMesh->SetupAttachment(GetMesh());
	ArmsMesh->SetMasterPoseComponent(GetMesh());


	// 캡슐 컴포넌트 크기 설정 (콜리전 범위)
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// 캐릭터가 움직일 때 카메라가 따라오도록 설정
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 200.f;
	CameraBoom->SocketOffset = FVector(0.f, 55.f, 65.f);
	CameraBoom->bUsePawnControlRotation = true;

	// 카메라가 캐릭터의 회전을 따라가도록 설정
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	// 캐릭터 이동 설정
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	PlayerCombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>(TEXT("PlayerCombatComponent"));
	PlayerInventoryComponent = CreateDefaultSubobject<UPlayerInventoryComponent>(TEXT("PlayerInventoryComponent"));
	PlayerUIComponent = CreateDefaultSubobject<UPlayerUIComponent>(TEXT("PlayerUIComponent"));
}

UPawnCombatComponent* APlayerCharacter::GetPawnCombatComponent() const
{
	return PlayerCombatComponent;
}

UPawnUIComponent* APlayerCharacter::GetPawnUIComponent() const
{
	return PlayerUIComponent;
}

UPlayerUIComponent* APlayerCharacter::GetPlayerUIComponent() const
{
	return PlayerUIComponent;
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (!CharacterStartUpData.IsNull())
	{
		if (UDataAsset_PlayerStartUpData* LoadedData = Cast<UDataAsset_PlayerStartUpData>(CharacterStartUpData.LoadSynchronous()))
		{
			// GAS 능력 부여
			LoadedData->GiveToAbilitySystemComponent(AbilitySystemComponent);

			PlayerInventoryComponent->ClearWeaponInventory();
			PlayerInventoryComponent->UnequipWeapon();

			if (LoadedData->ItemDataTable)
			{
				static const FString Context(TEXT("Startup Item Lookup"));

				// DataTable 전체 Row 가져오기
				TArray<FItemData*> AllRows;
				LoadedData->ItemDataTable->GetAllRows(Context, AllRows);

				for (FItemData* Row : AllRows)
				{
					if (!Row) continue;

					// Misc나 None은 스킵
					if (Row->ItemType == EItemType::Misc || Row->ItemType == EItemType::None)
						continue;

					// 지급할 개수 (DataTable MaxStack 기준)
					int32 GiveAmount = Row->MaxStack;

					// 인벤토리에 추가
					PlayerInventoryComponent->AddItem(*Row, GiveAmount);

		
					// 무기면 WeaponDataAsset도 등록
					//if (Row->ItemType == EItemType::Weapon01 ||
					//	Row->ItemType == EItemType::Weapon02 ||
					//	Row->ItemType == EItemType::Weapon03)
					//{
					//	if (Row->WeaponDataAsset.IsValid())
					//	{
					//		PlayerInventoryComponent->AddWeaponToInventory(Row->WeaponDataAsset.Get());
					//	}
					//	else if (UDataAsset_PlayerWeaponDatas* LoadedWeapon = Row->WeaponDataAsset.LoadSynchronous())
					//	{
					//		PlayerInventoryComponent->AddWeaponToInventory(LoadedWeapon);
					//	}
					//}

					// 특정 아이템은 벨트에 바로 장착
					if (Row->ItemID == FName("Pulse_Cell"))
					{
						PlayerInventoryComponent->EquipItemToBelt(Row->ItemID, EBeltType::UpperBelt);
					}
					else if (Row->ItemID == FName("Grinder"))
					{
						PlayerInventoryComponent->EquipItemToBelt(Row->ItemID, EBeltType::LowerBelt);
					}
					else if (Row->ItemID == FName("Body01") || Row->ItemID == FName("hair"))
					{
						PlayerInventoryComponent->EquipItem(Row->ItemType, Row->ItemID);
					}
				}
			}

			//// 기본 아이템 지급 (DataTable에서 찾아서)
			//if (LoadedData->ItemDataTable)
			//{
			//	static const FString Context(TEXT("Startup Item Lookup"));

			//	for (const FDefaultItemData& DefaultItem : LoadedData->DefaultPlayerItems)
			//	{
			//		if (FItemData* Row = LoadedData->ItemDataTable->FindRow<FItemData>(DefaultItem.ItemID, Context))
			//		{
			//			FName ItemID = Row->ItemID;

			//			switch (Row->ItemType)  // 예: 무기 / 방어구 / 소비 / 기타
			//			{
			//			case EItemType::Weapon01:
			//			case EItemType::Weapon02:
			//			case EItemType::Weapon03:
			//			{
			//				// 일반 인벤토리에 아이템 추가
			//				PlayerInventoryComponent->AddItem(*Row, DefaultItem.Quantity);

			//				// 무기 데이터 에셋 찾아서 지급
			//				if (Row->WeaponDataAsset.IsValid())
			//				{
			//					PlayerInventoryComponent->AddWeaponToInventory(Row->WeaponDataAsset.Get());
			//				}
			//				else if (UDataAsset_PlayerWeaponDatas* LoadedWeapon = Row->WeaponDataAsset.LoadSynchronous())
			//				{
			//					PlayerInventoryComponent->AddWeaponToInventory(LoadedWeapon);
			//				}
			//				break;
			//			}
			//			case EItemType::Misc:				
			//			case EItemType::None:				
			//			{
			//				break; // None이나 Misc는 지급 안함
			//			}

			//			default:
			//				// 일반 인벤토리에 아이템 추가
			//				PlayerInventoryComponent->AddItem(*Row, DefaultItem.Quantity);

			//				// 글라인더나 포션은 바로 장착
			//				if (ItemID == FName("Pulse_Cell"))
			//				{
			//					PlayerInventoryComponent->EquipItemToBelt(ItemID, EBeltType::UpperBelt);  // UpperBelt
			//				}
			//				else if (ItemID == FName("Grinder"))
			//				{
			//					PlayerInventoryComponent->EquipItemToBelt(ItemID, EBeltType::LowerBelt); // LowerBelt
			//				}
			//				break;
			//			}
			//		}
			//	}
			/*}*/
		}
	}
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("Forgot to assign a valid data asset as input config"));

	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);

	check(Subsystem);

	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	UPlayerInputComponent* MyPlayerInputComponent = CastChecked<UPlayerInputComponent>(PlayerInputComponent);

	// 기본 액션 바인딩
	MyPlayerInputComponent->BindNativeInputAction(InputConfigDataAsset, LOP_GameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Move);
	MyPlayerInputComponent->BindNativeInputAction(InputConfigDataAsset, LOP_GameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &APlayerCharacter::Input_Look);

	// 스위치 타겟 입력 바인딩
	MyPlayerInputComponent->BindNativeInputAction(InputConfigDataAsset, LOP_GameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggered);
	MyPlayerInputComponent->BindNativeInputAction(InputConfigDataAsset, LOP_GameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);

	MyPlayerInputComponent->BindNativeInputAction(InputConfigDataAsset, LOP_GameplayTags::InputTag_Interactable, ETriggerEvent::Started, this, &APlayerCharacter::Input_Interactable);

	// 능력 입력 액션 바인딩
	MyPlayerInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (MovementVector.IsNearlyZero()) return; // 입력 없으면 리턴

	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void APlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	// X축: 좌우 회전 (Yaw)
	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	// Y축: 상하 회전 (Pitch)
	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APlayerCharacter::Input_SwitchTargetTriggered(const FInputActionValue& InputActionValue)
{
	SwitchDirection = InputActionValue.Get<FVector2D>();
}

void APlayerCharacter::Input_SwitchTargetCompleted(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, SwitchDirection.X > 0.f ? LOP_GameplayTags::Player_Event_SwitchTarget_Right : LOP_GameplayTags::Player_Event_SwitchTarget_Left, Data
	);
}

void APlayerCharacter::Input_Interactable(const FInputActionValue& InputActionValue)
{
	FGameplayEventData Data;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		LOP_GameplayTags::Player_Event_Interact,
		Data
	);
}


void APlayerCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	AbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void APlayerCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	AbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}
