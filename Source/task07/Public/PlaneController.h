#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlaneController.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class TASK07_API APlaneController : public APlayerController
{
	GENERATED_BODY()

public:
	APlaneController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* InputMappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	virtual void BeginPlay() override;
};
