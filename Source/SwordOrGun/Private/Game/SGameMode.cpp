
#include "Game/SGameMode.h"
#include "Controllers/SPlayerController.h"
#include "Characters/SPlayerPawn.h"

ASGameMode::ASGameMode()
{
    PlayerControllerClass = ASPlayerController::StaticClass();
    // Ŭ���� ������ �Ѱ��ִ� ����: ���� ���α׷��Ӱ� �۾����ٵ�, �ν��Ͻ� �����δ�
    // �۾��� �� ���� ����. StaticClass(); : ������ �ܰ迡�� Ŭ���� ������ ������
    DefaultPawnClass = ASPlayerPawn::StaticClass();
}