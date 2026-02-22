# 🎮 P의 거짓 (Lies of P) 모작 포트폴리오


# ⚔️ 프로젝트 개요
> Lies of P에서 영감을 받은 GAS 기반 3D 액션 전투 시스템 구현 프로젝트  
> 전투, AI, 게임플레이 아키텍처 구조 설계 중심


> • 개발 인원: 1인 (개인 프로젝트)  
> • 개발 기간: 2025.07.07 ~ 2025.09.21 (11주)  
> • 개발 환경: Unreal Engine 5.4.4, Github   
> • 장르: 3인칭 액션 RPG / 전투 시스템 중심  

## 🎥 동영상
[![영상 미리보기](https://img.youtube.com/vi/6_0rvUXyf8w/0.jpg)](https://youtu.be/6_0rvUXyf8w)


## 📑 목차

- 🔍 GAS(Gameplay Ability System)를 선택한 이유
- 🎮 Core Systems (핵심 시스템)
  - ⚔ 전투 프레임워크 (GAS 기반)
  - 🗡 무기 충돌 판정 (Weapon Trace)
  - 🧠 AI 시스템 (BT + EQS + GAS)
  - 🎯 락온 시스템 (Target Lock-On)
  - 🎒 데이터 아키텍처 (Data Architecture)
  - 🧩 상호작용 시스템 (Interaction System)
  - 🚀 비동기 로딩 & 레벨 전환 (Async Loading)
  - 🛠 프로젝트 최적화 (Optimization)
- 🧪 게임플레이 GIF (Showcase)

---

# 🔍 GAS(Gameplay Ability System)를 선택한 이유

>이번 프로젝트는 단순히 전투 기능을 구현하는 것이 아니라,  
>**확장성과 유지보수성을 고려한 전투 아키텍처 설계**에 초점을 두었습니다.

>전투 로직을 Ability / GameplayEffect / GameplayTag 단위로 책임 분리하고,  
>콘텐츠가 확장되더라도 분기문이 증가하지 않는 구조를 설계하고자  
>Unreal Engine의 Gameplay Ability System(GAS)을 기반으로 구현했습니다.

또한, 임의로 시스템을 구성하기보다  
엔진이 제공하는 공식 아키텍처를 깊이 이해하고  
정석적인 방식으로 설계 경험을 쌓는 것을 목표로 했습니다.

<details>
<summary>자세한 설계 의도 펼치기/닫기</summary>
  
### 1️⃣ 구조적인 전투 시스템 설계

GAS는 Ability, Effect, AttributeSet, Tag 기반 구조를 통해  
전투 상태와 로직을 명확히 분리할 수 있는 아키텍처를 제공합니다.  
단순히 동작하는 전투 시스템이 아니라  
확장 가능한 구조를 설계하는 것이 목표였기 때문에 공식 프레임워크를 기반으로 구현했습니다.

### 2️⃣ 실제 상용 프로젝트와 유사한 개발 방식 경험

GAS는 멀티플레이, 예측 처리, 네트워크 동기화까지 고려된 구조입니다.  
비록 이번 프로젝트는 싱글 기반이지만,  
상용 게임에서 사용되는 구조를 이해하고 활용하는 경험을 쌓고자 선택했습니다.

### 3️⃣ 직접 구현보다 설계에 집중하기 위함

모든 기능을 커스텀 구현하는 대신  
엔진이 제공하는 구조를 이해하고 활용하는 데 집중했습니다.
이를 통해

- Ability 단위 책임 분리
- GameplayTag 기반 상태 제어
- GameplayEffect 기반 수치 처리
- 연출(GameplayCue)과 로직 분리

구조 중심 설계를 경험하고자 했습니다.

### 4️⃣ 확장성과 유지보수성 확보

무기 추가, 스킬 추가, 보스 패턴 확장 시  
로직 분기 증가가 아닌 Ability 추가 방식으로 확장되도록 설계했습니다.  
이는 전투 콘텐츠가 늘어날수록 구조가 복잡해지는 문제를 방지하기 위함입니다.

</details>

---

# 🎮 Core Systems (핵심 시스템)


## ⚔ 전투 프레임워크 (GAS 기반)

>이동, 공격, 구르기, 락온 등의 행동을 Ability 단위로 나누어 관리하고 있습니다.

### 설계 방향

- 공격 / 회피 / 스킬을 GameplayAbility로 분리
- 수치 계산은 GameplayEffect로 위임
- 상태는 GameplayTag로 관리
- Anim Notify 기반 입력 타이밍 제어
- 판정 로직과 연출(GameplayCue) 분리

>캐릭터 클래스 내부에 로직을 계속 추가하는 방식 대신,  
>Ability 단위로 쪼개어 BP를 추가하면 쉽게 확장 가능한 형태를 유지하려고 했습니다.

>또한 1인 프로젝트이기 때문에  
>과도하게 복잡한 범용 구조보다는  
>관리 가능한 선에서 확장성을 확보하는 것을 목표로 했습니다.

코어 로직은 C++(ASC/Ability 베이스)로 구현하고, 파생 Ability는 C++/BP로 분리해 데이터·연출은 BP에서 확장 가능하게 구성했습니다.



🔗 GameplayTag System 코드: [[LOP_GameplayTags.h](https://github.com/HaloTwo/LOP/blob/main/Source/LiseOfP/Public/LOP_GameplayTags.h)]   
   
🔗 ASC Systeam 코드: [[LOP_AbilitySystem](https://github.com/HaloTwo/LOP/tree/main/Source/LiseOfP/Public/AbilitySystem)]   

<details>
<summary> GAS 아키텍쳐 이미지 보기</summary>
  
![GAS 아키텍쳐](Image/LOP_GAS.png)
</details>

<details>
<summary> Player GA 폴더 구조 이미지 보기</summary>

![Player GA 폴더 구조](Image/GA폴더구조.png)
</details>


## 🗡 무기 충돌 판정 (Weapon Trace)

>무기 판정은 단순 Overlap이 아니라  
>Box Sweep 기반으로 구현했습니다.

>Overlap 방식은 프레임 단위로 충돌을 검사하기 때문에  
>공격 속도가 빠르거나, 한 프레임 사이 이동 거리가 큰 경우  
>적을 통과해버리는 문제가 발생할 수 있습니다.

>이를 방지하고, 실제 무기 궤적을 기준으로  
>보다 정확한 타격 위치를 계산하기 위해 Sweep 방식을 선택했습니다.

### 구현 방식

- `SweepMultiByChannel()` 사용
- 이전 프레임 위치와 현재 위치를 보간하여 궤적 기반 판정
- HitActor 캐싱으로 중복 타격 방지
- Physical Material 기반 재질별 파티클 분기

>빠른 공격 모션에서도 피격 누락이 발생하지 않도록 하는 데 중점을 두었습니다.   

🔗 Combat Component 코드: [[Components/Combat](https://github.com/HaloTwo/LOP/tree/main/Source/LiseOfP/Private/Components/Combat)]


## 🧠 AI 시스템 (BT + EQS + GAS)
>적 AI는 Behavior Tree 기반으로 구성했습니다.  
>공격은 플레이어와 동일하게 Ability를 사용하도록 설계했습니다.

>단순히 공격 애니메이션을 실행하는 구조가 아니라,  
>플레이어와 동일한 전투 시스템을 공유하도록 하여  
>구조를 통일하는 데 중점을 두었습니다.

### 구성

- Behavior Tree 기반 상태 제어
- EQS 기반 위치 탐색
- Ability 기반 공격 실행
- Phase를 DataAsset으로 분리

>패턴을 추가할 때 코드를 수정하기보다  
>데이터를 추가하는 방식으로 확장할 수 있도록 구성했습니다.

## 🎯 Target Lock-On 락온 시스템 (Target Lock-On)  

- Sphere 기반 타겟 탐색
- 거리 / 시야각 기반 후보 선택
- Camera Modifier 기반 회전 보정
- GameplayTag로 락온 상태 관리

>락온 상태를 Tag로 관리하여  
>이동, 대시, 회피 로직이 자연스럽게 분기되도록 설계했습니다.

## 🎒 데이터 아키텍처 (Data Architecture)

>전투 관련 대부분의 정보는 DataAsset으로 관리합니다.

- 무기 정보
- Ability 세트
- 보스 Phase 데이터
- 수치 정보(DataTable)

>코드 수정을 최소화하고,  
>필요하면 블루프린트나 데이터 수정만으로 확장 가능하도록 설계했습니다.

## 🧩 상호작용 시스템 (Interaction System)

> 플레이어가 상호작용 범위에 진입하면 HUD에 입력 프롬프트를 표시하고,  
> 지정된 키 입력 시 Ability를 통해 상호작용을 실행하는 구조로 구현했습니다.

- InteractableBase 부모 클래스를 기반으로 상호작용 객체 공통화
- Overlap 기반 범위 감지로 상호작용 대상 판별
- GameplayTag를 활용한 상호작용 타입 관리
- 입력 시 Interaction Ability 실행 구조
- Delegate를 통해 HUD Prompt 표시 및 제거 처리

> 현재는 보스룸 문(Door Interactable)에 Level Sequence 실행을 적용했으며,  
> 동일한 패턴으로 아이템 획득, 레버, NPC 대화 등  
> 다양한 상호작용 요소로 확장 가능하도록 부모-자식 구조로 설계했습니다.

> 또한 상호작용 로직을 캐릭터에 직접 구현하지 않고  
> Ability 기반으로 분리하여 전투 시스템(GAS)과 구조적 일관성을 유지했습니다.


## 🚀 비동기 로딩 & 레벨 전환 (Async Loading)

> 맵 규모로 인한 긴 로딩 시간을 줄이기 위해  
> StreamableManager 기반 비동기 로딩 + Commit 전환 구조를 구현했습니다.

- GameInstance에서 레벨을 GameplayTag로 매핑하여 관리
- RequestAsyncLoad로 레벨 에셋을 선 비동기 로딩
- 로딩 완료 시 Pending Level로만 보관
- 연출 및 입력 종료 시점에 OpenLevel로 실제 전환(Commit)
- UI는 Async Load Progress 값을 활용해 로딩 진행도 표시

> 선로딩 후 전환 시점을 제어하는 구조를 통해  
> 레벨 이동 시 발생하는 끊김을 최소화하고  
> 보다 자연스러운 씬 전환이 가능하도록 설계했습니다.


## 🛠 프로젝트 최적화 (Optimization)

> 초기 빌드에서는 프레임 저하와 로딩 지연이 크게 발생하여  
> 렌더링 및 씬 전반에 걸쳐 구조적 최적화를 적용했습니다.

- Texture Streaming Pool 조정으로 VRAM 사용량 관리
- Shadow 해상도 및 Cascade 수 감소로 GPU 부하 완화
- Lumen 반사 비활성화로 렌더링 비용 절감
- Early-Z PrePass 및 Occlusion Culling 활성화
- LOD 전환 거리 조정으로 불필요한 드로우콜 감소
- 과도한 Post Process 제거 후 최소 구성 유지

> 최적화 적용 후 빌드 기준 약 40FPS → 100FPS 수준으로 개선되었으며,  
> 플레이 중 프레임 드랍과 로딩 지연을 체감적으로 크게 줄일 수 있었습니다.

---


# 🧪 게임플레이 GIF

<details>
<summary>GIF 펼치기/닫기</summary>

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

</details>
