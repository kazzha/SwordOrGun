## 1. 게임 소개

-엔진 : UnrealEngine 5

-에디터: Microsoft Visual Studio 2022

-제작 기간: 약 한달

-개발 규모: 개인 개발

대검을 주무기로하는 RPG Character가 인간형 NPC와 전투 후 보스몬스터인 드래곤과 전투하는 게임입니다.

현재 루트슈터 전투 지원을 위한 TPS 캐릭터와 멀티플레이를 추가 중입니다.

설명 ppt 파일 다운로드 : http://naver.me/IMnTZnRw

## 2. 플레이 동영상

>Youtube

[![이미지](http://img.youtube.com/vi/vmNgwFHOfpk/0.jpg)](https://youtu.be/vmNgwFHOfpk)

## 3. 게임 플레이 전개도 
![슬라이드0001](https://github.com/kazzha/SwordOrGun/assets/137769077/b505026c-b135-4f24-a723-fbeb86c1a587)

## 4. 플레이어블 캐릭터 
![슬라이드0002](https://github.com/kazzha/SwordOrGun/assets/137769077/d6ad9c87-fc0e-4bf0-94ed-a0faa73243ef)
![슬라이드0005](https://github.com/kazzha/SwordOrGun/assets/137769077/15e02831-305b-444d-9680-8736a944132e)

* 스테이트 머신으로 움직이다가 죽음은 bool값으로 확인하여 bIsdead가 true일 시 죽음 모션 실행하도록 함
  
![스크린샷 2024-02-29 110422](https://github.com/kazzha/SwordOrGun/assets/137769077/eec54f7b-bb43-40cf-8bd7-9296fd84a9fe)

* 체력-캐릭터-위젯 관계
  
![슬라이드0004](https://github.com/kazzha/SwordOrGun/assets/137769077/1679e68c-fbc3-429f-aff6-6a6bdfe83cb7)



## 5. NPC와 비헤이비어 트리

![슬라이드0006](https://github.com/kazzha/SwordOrGun/assets/137769077/ed578dc8-b613-41a7-9bd5-fb4151a0273c)
![스크린샷 2024-02-19 202120](https://github.com/kazzha/SwordOrGun/assets/137769077/a5671c5b-8115-4887-bc37-7ca0811266be)
![스크린샷 2024-02-19 202137](https://github.com/kazzha/SwordOrGun/assets/137769077/b7680041-45c2-4ff7-9d96-b06936ab6bf0)

* DetectPlayerCharacter : 서비스 노드( 확인 시간 = 1초에 1번, 1초에 1번씩 근처에 플레이어가 있는지 확인)
* 그 이후 데코레이터 : TargetActor(플레이어)가 있으면 추격, 없으면 순찰
* IsInAttackRange 데코레이터 : 추격하게 되면 AttackRange 내에 있는지 판단


![슬라이드0007](https://github.com/kazzha/SwordOrGun/assets/137769077/d181af14-088d-42ae-bee5-c0beb16f7ce1)
순찰 -> 추적
![스크린샷 2024-02-29 131838](https://github.com/kazzha/SwordOrGun/assets/137769077/387dab85-45df-4e4e-87f6-568cb1efb177)
![스크린샷 2024-02-29 131855](https://github.com/kazzha/SwordOrGun/assets/137769077/c2e04688-23f3-4bae-9101-618655ab9f2f)


## 6. 콤보 공격 구현
![스크린샷 2024-02-19 202302](https://github.com/kazzha/SwordOrGun/assets/137769077/e9a1d225-5f14-44d4-b3d5-bd6ef9e05321)


* CheckHit AnimNotify : NPC가 공격에 맞았는지 확인
* CheckCanNextCombo AnimNotify : 이 전에 마우스 좌클릭이 한 번 더 들어오면 콤보로 판정하고 다음 공격행동 수행

## 7. TPS 캐릭터의 애니메이션 블렌딩
![제목-없는-동영상-Clipchamp로-제작-_1_](https://github.com/kazzha/SwordOrGun/assets/137769077/cfc026e6-8dd8-4961-91e5-7551cb719d84)

* 컨트롤 로테이션값을 받아와 부드러운 애니메이션이 될 수 있도록 블렌딩
