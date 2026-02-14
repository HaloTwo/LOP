// Vince Petrelli All Rights Reserved

#include "LOP_GameplayTags.h"

namespace LOP_GameplayTags
{
	// -------------------------------
	// 📌 Input Tags
	// -------------------------------
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Walk, "InputTag.Walk");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_DashAndRun, "InputTag.DashAndRun");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Equip, "InputTag.Equip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Unequip, "InputTag.Unequip");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interactable, "InputTag.Interactable");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Menu, "InputTag.Menu");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_UI_Back, "InputTag.UI.Back");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UI_Ok, "InputTag.UI.Ok");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UI_Right, "InputTag.UI.Right");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UI_Left, "InputTag.UI.Left");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UI_RightClick, "InputTag.UI.RightClick");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UI_LeftClick, "InputTag.UI.LeftClick");


	UE_DEFINE_GAMEPLAY_TAG(InputTag_UpperBeltSlot, "InputTag.UpperBeltSlot");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_LowerBeltSlot, "InputTag.LowerBeltSlot");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_UseItem, "InputTag.UseItem");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_LightAttack, "InputTag.LightAttack");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack, "InputTag.HeavyAttack");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_SwitchTarget, "InputTag.SwitchTarget");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld, "InputTag.MustBeHeld");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_MustBeHeld_Block, "InputTag.MustBeHeld.Block");

	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_Menu, "InputTag.Toggleable.Menu");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_Walk, "InputTag.Toggleable.Walk");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_TargetLock, "InputTag.Toggleable.TargetLock");

	// -------------------------------
	// 📌 Player Events
	// -------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_EquipStart, "Player.Event.EquipStart");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_EquipEnd, "Player.Event.EquipEnd");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_UnEquip, "Player.Event.UnEquip");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_HitPause, "Player.Event.HitPause");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SuccessfulBlock, "Player.Event.SuccessfulBlock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Left, "Player.Event.SwitchTarget.Left");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_SwitchTarget_Right, "Player.Event.SwitchTarget.Right");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Interactable, "Player.Event.Interactable");
	UE_DEFINE_GAMEPLAY_TAG(Player_Event_Interact, "Player.Event.Interact");

	// -------------------------------
	// 📌 Player Status
	// -------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_DashAndRun, "Player.Status.DashAndRun");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_ComboAttack_LightAttack, "Player.Status.ComboAttack.LightAttack");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_ComboAttack_HeavyAttack, "Player.Status.ComboAttack.HeavyAttack");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_StaminaBlocked, "Player.Status.StaminaBlocked");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Blocking, "Player.Status.Blocking");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_TargetLock, "Player.Status.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Status_Walk, "Player.Status.Walk");

	// -------------------------------
	// 📌 SetByCaller Tags
	// -------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Light, "Player.SetByCaller.AttackType.Light");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_AttackType_Heavy, "Player.SetByCaller.AttackType.Heavy");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_Stamina, "Player.SetByCaller.Stamina");
	UE_DEFINE_GAMEPLAY_TAG(Player_SetByCaller_Health, "Player.SetByCaller.Health");
	UE_DEFINE_GAMEPLAY_TAG(Shared_SetByCaller_BaseDamage, "Shared.SetByCaller.BaseDamage");

	// -------------------------------
	// 📌 Shared Abilities
	// -------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_HitReact, "Shared.Ability.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Ability_Death, "Shared.Ability.Death");

	// -------------------------------
	// 📌 Shared Events
	// -------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_MeleeHit, "Shared.Event.MeleeHit");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_HitReact, "Shared.Event.HitReact");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Event_BattleBegin, "Shared.Event.BattleBegin");

	// -------------------------------
	// 📌 Shared Status
	// -------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_Dead, "Shared.Status.Dead");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Front, "Shared.Status.HitReact.Front");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Left, "Shared.Status.HitReact.Left");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Right, "Shared.Status.HitReact.Right");
	UE_DEFINE_GAMEPLAY_TAG(Shared_Status_HitReact_Back, "Shared.Status.HitReact.Back");

	// -------------------------------
	// ⚔ Player Weapon Abilities
	// -------------------------------

	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_TargetLock, "Player.Ability.TargetLock");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_UpperBeltSlotMove, "Player.Ability.UpperBeltSlotMove");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_LowerBeltSlotMove, "Player.Ability.LowerBeltSlotMove");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_UseItem, "Player.Ability.UseItem");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Interractable_Door, "Player.Ability.Interractable.Door");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Interractable_Item, "Player.Ability.Interractable.Item");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_UI, "Player.Ability.Equip.UI");

	// └ 장착
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Saber, "Player.Ability.Equip.Saber");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Bayonet, "Player.Ability.Equip.Bayonet");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Equip_Rapier, "Player.Ability.Equip.Rapier");

	// └ 비장착
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Saber, "Player.Ability.Unequip.Saber");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Bayonet, "Player.Ability.Unequip.Bayonet");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Unequip_Rapier, "Player.Ability.Unequip.Rapier");

	// └ 대시
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_DashAndRun_Saber, "Player.Ability.DashAndRun.Saber");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_DashAndRun_Bayonet, "Player.Ability.DashAndRun.Bayonet");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_DashAndRun_Rapier, "Player.Ability.DashAndRun.Rapier");

	// └ 걷기
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Walk_Saber, "Player.Ability.Walk.Saber");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Walk_Bayonet, "Player.Ability.Walk.Bayonet");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Walk_Rapier, "Player.Ability.Walk.Rapier");

	// └ HitPause (무기별로 다를 경우)
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause_Saber, "Player.Ability.HitPause.Saber");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause_Bayonet, "Player.Ability.HitPause.Bayonet");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_HitPause_Rapier, "Player.Ability.HitPause.Rapier");

	// └ 공격 (Light)
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Saber, "Player.Ability.Attack.Light.Saber");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Bayonet, "Player.Ability.Attack.Light.Bayonet");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Light_Rapier, "Player.Ability.Attack.Light.Rapier");

	// └ 공격 (Heavy)
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Saber, "Player.Ability.Attack.Heavy.Saber");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Bayonet, "Player.Ability.Attack.Heavy.Bayonet");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Attack_Heavy_Rapier, "Player.Ability.Attack.Heavy.Rapier");

	// └ 블록 (무기별로 다를 경우)
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Block_Saber, "Player.Ability.Block.Saber");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Block_Bayonet, "Player.Ability.Block.Bayonet");
	UE_DEFINE_GAMEPLAY_TAG(Player_Ability_Block_Rapier, "Player.Ability.Block.Rapier");

	// -------------------------------
	// 🗡️ Player Weapon Tags
	// -------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Saber, "Player.Weapon.Saber");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Bayonet, "Player.Weapon.Bayonet");
	UE_DEFINE_GAMEPLAY_TAG(Player_Weapon_Rapier, "Player.Weapon.Rapier");

	// -------------------------------
	// 👹 Enemy Tags
	// -------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_1, "Enemy.Ability.Melee.1");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_2, "Enemy.Ability.Melee.2");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_3, "Enemy.Ability.Melee.3");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_4, "Enemy.Ability.Melee.4");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_5, "Enemy.Ability.Melee.5");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_6, "Enemy.Ability.Melee.6");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_7, "Enemy.Ability.Melee.7");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_8, "Enemy.Ability.Melee.8");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_9, "Enemy.Ability.Melee.9");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Melee_10, "Enemy.Ability.Melee.10");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_Ranged, "Enemy.Ability.Ranged");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_PhaseChange, "Enemy.Ability.PhaseChange");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Ability_SpawnWaitting, "Enemy.Ability.SpawnWaitting");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Weapon, "Enemy.Weapon");

	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_ComboAttack, "Enemy.Event.ComboAttack");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_PhaseChange, "Enemy.Event.PhaseChange");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Event_SpawnWattingEnd, "Enemy.Event.SpawnWattingEnd");
	// -------------------------------
	// 👹 Enemy Status Tags
	// -------------------------------
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Strafing, "Enemy.Status.Strafing");
	UE_DEFINE_GAMEPLAY_TAG(Enemy_Status_Phase2, "Enemy.Status.Phase2");


	UE_DEFINE_GAMEPLAY_TAG(GameData_Level_MainGameMap, "GameData.Level.MainGameMap");
	UE_DEFINE_GAMEPLAY_TAG(GameData_Level_MainMenuMap, "GameData.Level.MainMenuMap");
	UE_DEFINE_GAMEPLAY_TAG(GameData_Level_LoadingMap, "GameData.Level.LoadingMap");
}
