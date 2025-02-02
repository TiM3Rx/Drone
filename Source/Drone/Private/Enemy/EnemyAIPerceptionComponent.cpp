#include "Enemy/EnemyAIPerceptionComponent.h"
#include "Enemy/EnemyAIController.h"
#include "Drone/BaseDrone.h"
#include "Enemy/Turret.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"

AActor* UEnemyAIPerceptionComponent::GetPlayerCharacter()
{
    TArray<AActor*> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if (PercieveActors.Num() == 0)
    {
        GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);
        if (PercieveActors.Num() == 0)
            return nullptr;
    }
    if (PercieveActors.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No perceivable actors detected!"));
    }

    AActor* Character = nullptr;
    for (const auto PercieveActor : PercieveActors)
    {
        const auto PlayerActor = Cast<ABaseDrone>(PercieveActor);
        if (!PlayerActor)
        {
            continue;
        }
        else

        {
            Character = PlayerActor;
        }
    }
    return Character;
}

FVector UEnemyAIPerceptionComponent::GetPlayerLocation()
{
    if (!GetPlayerCharacter())
    {
        UE_LOG(LogTemp, Display, TEXT("PlayerCharacter is not valid"));
        return FVector::ZeroVector;
    }
    return GetPlayerCharacter()->GetActorLocation();
}
