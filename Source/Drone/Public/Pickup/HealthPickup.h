#pragma once

#include "CoreMinimal.h"
#include "Pickup/BasePickup.h"
#include "HealthPickup.generated.h"

UCLASS()
class DRONE_API AHealthPickup : public ABasePickup
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	int32 HealAmount = 50.0f;

private:
	virtual bool GivePickupTo(APawn* PlayerPawn) override;

};
