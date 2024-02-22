
#include "Game/SGameMode.h"
#include "Controllers/SPlayerController.h"
#include "Characters/SPlayerPawn.h"
#include "Game/SPlayerState.h"


ASGameMode::ASGameMode()
{
    PlayerControllerClass = ASPlayerController::StaticClass();
    // 클래스 정보를 넘겨주는 이유: 여러 프로그래머가 작업할텐데, 인스턴스 정보로는
    // 작업할 수 없기 때문. StaticClass(); : 컴파일 단계에서 클래스 정보를 가져옴
    DefaultPawnClass = ASPlayerPawn::StaticClass();

   
}

void ASGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    ASPlayerState* PlayerState = NewPlayer->GetPlayerState<ASPlayerState>();
    if (true == ::IsValid(PlayerState))
    {
        PlayerState->InitPlayerState();
    }

}

