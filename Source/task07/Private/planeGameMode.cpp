#include "planeGameMode.h"
#include "AirPlane01.h"
#include "PlaneController.h"

AplaneGameMode::AplaneGameMode()
{
	static ConstructorHelpers::FClassFinder<AAirPlane01>
	PlayerCharacter(TEXT("/Game/blueprints/BP_AirPlane01"));
	if (PlayerCharacter.Succeeded())
	{
		DefaultPawnClass = PlayerCharacter.Class;
	}

	static ConstructorHelpers::FClassFinder<APlaneController>PlayerController(TEXT("/Game/blueprints/BP_PlaneController"));
	if (PlayerController.Succeeded())
	{
		PlayerControllerClass = PlayerController.Class;
	}
}