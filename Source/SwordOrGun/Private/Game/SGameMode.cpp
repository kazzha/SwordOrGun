
#include "Game/SGameMode.h"
#include "Controllers/SPlayerController.h"
#include "Characters/SPlayerPawn.h"
#include "Game/SPlayerState.h"


ASGameMode::ASGameMode()
{
    PlayerControllerClass = ASPlayerController::StaticClass();
    // Ŭ���� ������ �Ѱ��ִ� ����: ���� ���α׷��Ӱ� �۾����ٵ�, �ν��Ͻ� �����δ�
    // �۾��� �� ���� ����. StaticClass(); : ������ �ܰ迡�� Ŭ���� ������ ������
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

