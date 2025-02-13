#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AirPlane01.generated.h"

class UBoxComponent;
class USkeletalMeshComponent;
class UArrowComponent;
class USpringArmComponent;
class UCameraComponent;

struct FInputActionValue;

UCLASS()
class TASK07_API AAirPlane01 : public APawn
{
	GENERATED_BODY()

public:
	AAirPlane01();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Plane|Components")
	UBoxComponent* BoxComp;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Plane|Components")
	USkeletalMeshComponent* SkeletalMeshComp;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Plane|Components")
	UArrowComponent* ArrowComp;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera");
	UCameraComponent* CameraComp;

	FVector CurrentLocation;
	FRotator CurrentRotation;
	float RotateValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Plane|Movements")
	float Movespeed;


private:
	UFUNCTION()
	void Move(const FInputActionValue& value);
	UFUNCTION()
	void MoveStop(const FInputActionValue& value);
	UFUNCTION()
	void Look(const FInputActionValue& value);
};
