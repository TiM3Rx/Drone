#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Turret.generated.h"

class UHealthComponent;
class UBehaviorTree;
class AProjectile;

UCLASS()
class DRONE_API ATurret : public ACharacter
{
    GENERATED_BODY()

public:
    ATurret();

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    TObjectPtr<UBehaviorTree> BehaviorTreeAsset;
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UHealthComponent> HealthComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AProjectile> ProjectileClass;

    virtual void BeginPlay() override;
    void OnDeath();
    void OnHealthChanged(float Health, float HealthDelta);

    UFUNCTION(BlueprintCallable)
    void Fire();

};
