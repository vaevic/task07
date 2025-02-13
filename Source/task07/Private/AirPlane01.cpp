#include "AirPlane01.h"
#include "PlaneController.h" //컨트롤러 헤더 추가
#include "EnhancedInputComponent.h" //헤더 추가
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAirPlane01::AAirPlane01()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(BoxComp);
	BoxComp->SetSimulatePhysics(false);
	BoxComp->SetBoxExtent(FVector(440.0f, 577.0f, 184.0f));
	
	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComp->SetupAttachment(RootComponent);
	SkeletalMeshComp->SetSimulatePhysics(false);
	SkeletalMeshComp->SetRelativeLocation(FVector(124.0f, 0.0f, -12.0f));
	SkeletalMeshComp->SetRelativeRotation(FRotator(-180.0f, 90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Fab/WW_Plane/ww_plane.ww_plane"));
	if (MeshAsset.Succeeded())
	{
		SkeletalMeshComp->SetSkeletalMesh(MeshAsset.Object);
	}

	ArrowComp = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	ArrowComp->SetupAttachment(RootComponent);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 800.0f;
	SpringArmComp->SocketOffset = FVector(0.0f, 300.0f, 530.0f);
	SpringArmComp->bUsePawnControlRotation = false;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);
	CameraComp->SetRelativeRotation(FRotator(-20.0f, 0.0f, 0.0f));
	CameraComp->bUsePawnControlRotation = false;

	Movespeed = 15.0f;
	RotateValue = 1.0f;
	MaxRotateValue = 10.0f;

}



void AAirPlane01::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (APlaneController* PlayerController = Cast<APlaneController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &AAirPlane01::Move);
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Completed, this, &AAirPlane01::MoveStop);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &AAirPlane01::Look);
			}
		}
	}
}

void AAirPlane01::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))// 전후
	{
		CurrentLocation = FVector::ZeroVector;
		CurrentLocation.X = MoveInput.X*Movespeed;
		AddActorLocalOffset(CurrentLocation);

		//if (CurrentRotation.Pitch <= MaxRotateValue)
		//{
		//	CurrentRotation = FRotator::ZeroRotator;
		//	CurrentRotation.Pitch += RotateValue;
		//	//SpringArmComp->SetRelativeRotation(CurrentRotation);
		//	SpringArmComp->AddLocalRotation(CurrentRotation);
		//}
		
	}

	if (!FMath::IsNearlyZero(MoveInput.Y)) //좌우
	{
		CurrentLocation = FVector::ZeroVector;
		CurrentLocation.Y = MoveInput.Y*Movespeed;
		AddActorLocalOffset(CurrentLocation);

		//CurrentRotation = FRotator::ZeroRotator;
		//CurrentRotation.Roll -= RotateValue;
		//SpringArmComp->SetRelativeRotation(CurrentRotation);
		//SpringArmComp->AddLocalRotation(CurrentRotation);
	}	
}

void AAirPlane01::MoveStop(const FInputActionValue& value)
{
	/*FRotator RetrunRotation = */
	//SpringArmComp->AddLocalRotation(CurrentRotation);
}

void AAirPlane01::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();
		
	CurrentRotation = FRotator::ZeroRotator;
	CurrentRotation.Yaw = LookInput.X;
	CurrentRotation.Pitch = -LookInput.Y;
	AddActorLocalRotation(CurrentRotation);

	/*SpringArmComp->AddLocalRotation(CurrentRotation);*/
	//GetWorld()->GetFirstPlayerController()->AddYawInput(CurrentRotation.Yaw);
	//GetWorld()->GetFirstPlayerController()->AddPitchInput(CurrentRotation.Pitch);	
}

void AAirPlane01::BeginPlay()
{
	Super::BeginPlay();
}

void AAirPlane01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}