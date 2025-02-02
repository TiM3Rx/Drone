#include "Pickup/HealthPickup.h"
#include "Drone/BaseDrone.h"
#include "HealthComponent.h"

bool AHealthPickup::GivePickupTo(APawn* PlayerPawn)
{
    ABaseDrone* Player = Cast<ABaseDrone>(PlayerPawn);
    if (!Player)
        return false;
    UActorComponent* Component = PlayerPawn->GetComponentByClass(UHealthComponent::StaticClass());
    UHealthComponent* HealthComponent = Cast<UHealthComponent>(Component);
    if (!HealthComponent)
        return false;

    HealthComponent->PickupHealth(HealAmount);
    return true;
}
