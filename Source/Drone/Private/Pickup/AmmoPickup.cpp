#include "Pickup/AmmoPickup.h"
#include "Drone/BaseDrone.h"

bool AAmmoPickup::GivePickupTo(APawn* PlayerPawn)
{
    ABaseDrone* Player = Cast<ABaseDrone>(PlayerPawn);
    if (!Player)return false;
    Player->SetAmmoData(AmmoAmount);
    return true;
}
