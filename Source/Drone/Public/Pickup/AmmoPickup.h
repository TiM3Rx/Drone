#pragma once

#include "CoreMinimal.h"
#include "Pickup/BasePickup.h"
#include "AmmoPickup.generated.h"

UCLASS()
class DRONE_API AAmmoPickup : public ABasePickup
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	int32 AmmoAmount = 5.0f;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
