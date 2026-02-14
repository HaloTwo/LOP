// Vince Petrelli All Rights Reserved

#pragma once

#include "NativeGameplayTags.h"

namespace LOP_GameplayTags
{
	// -------------------------------
	// 📌 Input Tags (공용)
	// -------------------------------
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Walk);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_DashAndRun);

	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Equip);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Unequip);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Menu);

	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UI_Back);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UI_Ok);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UI_Right);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UI_Left);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UI_RightClick);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UI_LeftClick);

	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UpperBeltSlot);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LowerBeltSlot);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UseItem);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Interactable);

	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack);

	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SwitchTarget);

	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld_Block);

	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_Walk);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_Menu);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_TargetLock);

	// -------------------------------
	// 📌 Player Events
	// -------------------------------
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_EquipStart);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_EquipEnd);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_UnEquip);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SuccessfulBlock);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Left);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Right);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Interactable);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Interact);


	// -------------------------------
	// 📌 Player Status
	// -------------------------------
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_DashAndRun);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_ComboAttack_LightAttack);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_ComboAttack_HeavyAttack);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_StaminaBlocked);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Blocking);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_TargetLock)
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Walk)

	// -------------------------------
	// 📌 SetByCaller Tags
	// -------------------------------
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_Stamina);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_Health);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);

	// -------------------------------
	// 📌 Shared Abilities
	// -------------------------------
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);

	// -------------------------------
	// 📌 Shared Events
	// -------------------------------
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_BattleBegin);

	// -------------------------------
	// 📌 Shared Status
	// -------------------------------
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Front);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Left);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Right);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Back);

	// -------------------------------
	// ⚔ Player Weapon Abilities (무기별로 전부 분리)
	// -------------------------------

	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_TargetLock);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_UpperBeltSlotMove);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_LowerBeltSlotMove);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_UseItem);

	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Interractable_Door);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Interractable_Item);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_UI);

	// └ 장착
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Saber);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Bayonet);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Rapier);

	// └ 비장착
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Saber);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Bayonet);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Rapier);

	// └ 대시
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_DashAndRun_Saber);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_DashAndRun_Bayonet);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_DashAndRun_Rapier);

	// └ 걷기
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Walk_Saber);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Walk_Bayonet);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Walk_Rapier);

	// └ HitPause (공용 유지 가능하나 분리 시 아래처럼)
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause_Saber);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause_Bayonet);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause_Rapier);

	// └ 공격 (Light)
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Saber);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Bayonet);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Rapier);

	// └ 공격 (Heavy)
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Saber);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Bayonet);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Rapier);

	// └ 블록 (Block)
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Block_Saber);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Block_Bayonet);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Block_Rapier);

	// -------------------------------
	// 🗡️ Player Weapon Tags
	// -------------------------------
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Saber);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Bayonet);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Rapier);

	// -------------------------------
	// 👹 Enemy Tags
	// -------------------------------
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_1);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_2);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_3);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_4);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_5);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_6);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_7);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_8);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_9);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee_10);

	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_PhaseChange);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SpawnWaitting);

	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);

	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Event_ComboAttack);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Event_PhaseChange);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Event_SpawnWattingEnd);

	// -------------------------------
	// 📌 Enemy Status
	// -------------------------------
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Phase2);


	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_Level_MainGameMap);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_Level_MainMenuMap);
	LISEOFP_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_Level_LoadingMap);
}
