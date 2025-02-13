#include "PlaneController.h"
#include "EnhancedInputSubsystems.h"

APlaneController::APlaneController()
	:InputMappingContext(nullptr),
	MoveAction(nullptr),
	LookAction(nullptr)
{

}

void APlaneController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}
}