#include "UI/DroneHUD.h"
#include "UI/DroneUserWidget.h"

void ADroneHUD::BeginPlay()
{
	Super::BeginPlay();
	auto PlayerHUD = CreateWidget<UUserWidget>(GetWorld(), DroneHUDWidgetClass);
	if (PlayerHUD)
	{
		PlayerHUD->AddToViewport();
	}
}
