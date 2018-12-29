#include "CCharacter.h"



void CCharacter::beDamaged(int HP)
{
	this->SetHP(this->GetHP() - HP);
	int k = this->GetHP();
}



CCharacter::CCharacter()
{
}


CCharacter::~CCharacter()
{
}
