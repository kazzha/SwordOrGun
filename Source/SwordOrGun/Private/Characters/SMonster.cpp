// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SMonster.h"

ASMonster::ASMonster()
{
}

void ASMonster::BeginPlay()
{
}

float ASMonster::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return 0.0f;
}

void ASMonster::SetWidget(USwordUserWidget* InSwordUserWidget)
{
}

void ASMonster::Attack()
{
}

void ASMonster::OnAttackAnimMontageEnded(UAnimMontage* Montage, bool bIsInterrupt)
{
}
