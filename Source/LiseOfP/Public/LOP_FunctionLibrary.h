// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LOP_FunctionLibrary.generated.h"

class ULOP_AbilitySystemComponent;
class UPawnCombatComponent;
class ULOP_GameInstance;

UENUM()
enum class EWarriorConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EWarriorValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EWarriorSuccessType : uint8
{
	Successful,
	Failed
};

UENUM(BlueprintType)
enum class EWeaponScalingGrade : uint8
{
	None     UMETA(DisplayName = "None"),
	S          UMETA(DisplayName = "S"),
	A          UMETA(DisplayName = "A"),
	B          UMETA(DisplayName = "B"),
	C          UMETA(DisplayName = "C"),
	D          UMETA(DisplayName = "D")
};

UENUM(BlueprintType)
enum class EGameTeam : uint8
{
	Player = 0,
	Enemy = 1,
	Boss = 2,
	NPC = 3,
	Ally = 4
};

UENUM(BlueprintType)
enum class ECardinal8 : uint8
{
	Front,
	FrontRight,
	Right,
	BackRight,
	Back,
	BackLeft,
	Left,
	FrontLeft
};

UENUM(BlueprintType)
enum class EWarriorInputMode : uint8
{
	GameOnly,
	UIOnly,
	GameAndUI
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	None,
	Weapon01,
	Weapon02,
	Weapon03,
	Clothes,
	Helmet,
	Almulet,
	Ring,
	Arms,
	Consumable,  
	Usable,      
	Misc        
};

UENUM(BlueprintType)
enum class EWeaponType : uint8
{
	OneHand,
	TwoHand,
};



/**
 * 
 */

UCLASS()
class LISEOFP_API ULOP_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static ULOP_AbilitySystemComponent* NativeGetWarriorASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary")
	static void RemoveGameplayFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary", meta = (DisplayName = "Does Actor Have Tag", ExpandEnumAsExecs = "OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck, EWarriorConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary", meta = (DisplayName = "Get Pawn Combat Component From Actor", ExpandEnumAsExecs = "OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EWarriorValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "Warrior|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure, Category = "Warrior|FunctionLibrary")
	static FGameplayTag HitReactDirectionTag(const AActor* InAttacker, const AActor* InTarget, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "Warrior|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintPure, Category = "Movement|Direction")
	static ECardinal8 DirectionLocalFromPlayer(const APlayerCharacter* Player);


	UFUNCTION(BlueprintCallable, Category = "Warrior|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static void ToggleInputMode(const UObject* WorldContextObject, EWarriorInputMode InInputMode);


	UFUNCTION(BlueprintPure, Category = "Warrior|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static ULOP_GameInstance* GetLOP_GameInstance(const UObject* WorldContextObject);
};


