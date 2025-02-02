#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, float);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DRONE_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHealthComponent();

    bool PickupHealth(int32 HealthAmount);

    void SetHealth(float NewHealth);
    float GetHealth() { return Health; }

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const;

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const;

    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged; 

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "1000"))
    float MaxHealth = 100.0f;


    virtual void BeginPlay() override;

private:
    float Health = 0.0f;

    void ApplyDamage(float Damage, AController* InstigatedBy);

    UFUNCTION()
    void OnTakePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation,
        class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
        const class UDamageType* DamageType, AActor* DamageCauser);
};
