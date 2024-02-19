## 1. 게임 소개

-엔진 : UnrealEngine 5

-에디터: Microsoft Visual Studio 2022

-제작 기간: 약 한달

-개발 규모: 개인 개발

대검을 주무기로하는 RPG Character가 인간형 NPC와 전투 후 보스몬스터인 드래곤과 전투하는 게임입니다.
현재 루트슈터 전투 지원을 위한 TPS 캐릭터와 멀티플레이를 추가 중입니다.

## 2. 플레이 동영상

>Youtube

[![이미지](http://img.youtube.com/vi/JAWqFXuF3xc/0.jpg)](https://www.youtube.com/watch?v=JAWqFXuF3xc)

## 3. 게임 플레이 전개도 


## 4. 상속 관계도
![언리얼엔진5 포트폴리오](https://github.com/kazzha/SwordOrGun/assets/137769077/bf5431e1-0459-40df-9dfe-a62f7ef9fcab)

## 5. NPC 비헤이비어 트리
![스크린샷 2024-02-19 202120](https://github.com/kazzha/SwordOrGun/assets/137769077/a5671c5b-8115-4887-bc37-7ca0811266be)
![스크린샷 2024-02-19 202137](https://github.com/kazzha/SwordOrGun/assets/137769077/b7680041-45c2-4ff7-9d96-b06936ab6bf0)
* DetectPlayerCharacter : 서비스 노드( 확인 시간 = 1초에 1번, 1초에 1번씩 근처에 플레이어가 있는지 확인)
* 그 이후 데코레이터 : TargetActor(플레이어)가 있으면 추격, 없으면 순찰
* IsInAttackRange 데코레이터 : 추격하게 되면 AttackRange 내에 있는지 판단

## 6. 콤보 공격 구현
![스크린샷 2024-02-19 202302](https://github.com/kazzha/SwordOrGun/assets/137769077/e9a1d225-5f14-44d4-b3d5-bd6ef9e05321)

* CheckHit AnimNotify : NPC가 공격에 맞았는지 확인
* CheckCanNextCombo AnimNotify : 이 전에 마우스 좌클릭이 한 번 더 들어오면 콤보로 판정하고 다음 공격행동 수행

## 7. TPS 캐릭터의 애니메이션 블렌딩
![스크린샷 2024-02-19 202401](https://github.com/kazzha/SwordOrGun/assets/137769077/4c5044d7-5e80-42ab-bdaf-f8d7a3b06966)
* 컨트롤 로테이션값을 받아와 부드러운 애니메이션이 될 수 있도록 블렌딩
