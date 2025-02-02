#include "DroneGameMode.h"
#include "Drone/BaseDrone.h"
#include "UObject/ConstructorHelpers.h"

ADroneGameMode::ADroneGameMode() : Super()
{
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Drone/BP_BaseDrone"));
    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}
