#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DroneHUD.generated.h"

UCLASS()
class DRONE_API ADroneHUD : public AHUD
{
	GENERATED_BODY()
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> DroneHUDWidgetClass;

    virtual void BeginPlay()override;
};
