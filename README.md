# ⚔️ UE5 Action RPG (Lies of P Inspired)

> ‘P의 거짓(Lies of P)’ 전투 구조를 레퍼런스로 제작한  
> Unreal Engine 5 기반 3인칭 액션 전투 시스템 포트폴리오입니다.  
> (전투 시스템, AI, Lock-On, Gameplay Architecture 중심 구현)

---

## 📌 Project Info
> • 개발 인원: 1인 (개인 프로젝트)  
> • 개발 기간: 2025.07.07 ~ 2025.09.21 (11주)  
> • 개발 환경: Unreal Engine 5.4.4, C++, Blueprint, GitHub  
> • 장르: 3인칭 액션 RPG (Combat System Focus)  
---

## 🎥 Demo Video
[![영상 미리보기](https://img.youtube.com/vi/영상ID/0.jpg)](유튜브링크)

---

# 🧪 Gameplay GIF (핵심 기능)

## 1. 🧱 재질별 충돌 파티클 시스템
> 무기 충돌 시 재질(철/목재/석재)에 따라 다른 파티클이 출력되도록 구현

| Material Impact |
|----------------|
| ![](Image/1.gif) |

---

## 2. ⚔ 공격 캔슬 & 연속 콤보 시스템
> Anim Notify 기반 공격 캔슬 및 연속 입력 처리 로직 구현

| 1타 공격 | 연속 콤보 |
|----------|-----------|
| ![](Image/2-1.gif) | ![](Image/2-2.gif) |

---

## 3. 🗡 무기별 공격 판정 & 보정 시스템
> Weapon Trace 기반 무기 타입별 판정 범위 및 타격 보정 처리

| Saber | Rapier | Bayonet |
|-------|--------|---------|
| ![](Image/3.Saber.gif) | ![](Image/3.Repair.gif) | ![](Image/3.Bayonet.gif) |

---

## 4. 👹 Boss AI & Phase 패턴 시스템
> Behavior Tree 기반 보스 AI 및 Phase 전환 패턴 구현

| Phase 1 | Phase 2 |
|---------|---------|
| ![](Image/4.Boss1.gif) | ![](Image/4.Boss3.gif) |

| Phase 1 (Variant) | Phase 2 (Variant) |
|-------------------|-------------------|
| ![](Image/4.Boss2.gif) | ![](Image/4.Boss4.gif) |

---

# 🎮 Core Systems (코드 연동)

## ⚔ Combat System (GAS 기반 전투 구조)
> Gameplay Ability System(GAS)을 기반으로 전투 상태, 스킬, 판정 구조를 설계  
> 공격 판정, 콤보 입력, 상태 전이를 시스템 단위로 분리 구현

🔗 Code: (Combat / Ability 코드 링크)

---

## 🎯 Target Lock-On System
> 주변 적 탐색 후 타겟 고정 및 카메라 보정 시스템 구현  
> 전투 중 시점 유지 및 타겟 전환 로직 포함

🔗 Code: (LockOn 코드 링크)

---

## 🧠 AI System (Behavior Tree + EQS)
> Behavior Tree 기반 적 AI 상태 제어  
> EQS를 활용한 플레이어 탐색 및 전투 진입 로직 구현  
> 보스 Phase 전환 패턴 설계

🔗 Code: (AI 코드 링크)

---

## 🎒 Inventory & Data Architecture
> DataAsset 기반 무기 및 스킬 데이터 구조 설계  
> 데이터 기반 장비 및 전투 시스템 연동 구조 구현

🔗 Code: (Inventory / Data 코드 링크)
