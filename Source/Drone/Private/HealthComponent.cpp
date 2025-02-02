#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

}

bool UHealthComponent::PickupHealth(int32 HealthAmount)
{
    if (Health == MaxHealth)
    {
        return false;
    }
    SetHealth(Health + HealthAmount);
    return true;
}

void UHealthComponent::SetHealth(float NewHealth)
{
    const float NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const float DeltaHealth = NextHealth - Health;

    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, DeltaHealth);
}

bool UHealthComponent::IsDead() const
{
    return FMath::IsNearlyZero(Health);
}

float UHealthComponent::GetHealthPercent() const
{
    return Health / MaxHealth;;
}

void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0);

    Health = MaxHealth;

    AActor* ComponentActor = GetOwner();
    if (ComponentActor)
    {
        ComponentActor->OnTakePointDamage.AddDynamic(this, &UHealthComponent::OnTakePointDamage);
    }

}

void UHealthComponent::ApplyDamage(float Damage, AController* InstigatedBy)
{
    if (Damage <= 0 || IsDead() || !GetWorld())
        return;
    SetHealth(Health - Damage);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
}

void UHealthComponent::OnTakePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy,
    FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
    const UDamageType* DamageType, AActor* DamageCauser)
{
    ApplyDamage(Damage, InstigatedBy);
}

