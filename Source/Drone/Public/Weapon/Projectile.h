#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class DRONE_API AProjectile : public AActor
{
    GENERATED_BODY()

public:
    AProjectile();

    void SetShotDirection(const FVector& Direction);


protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
    TObjectPtr<USphereComponent> SphereComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
    float DamageAmount = 40.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
    float LifeSeconds = 5.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Explosion")
    float DamageRadius = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion")
    FColor ExplosionColor = FColor::Red;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Explosion")
    float ExplosionDuration = 3.0f;

    virtual void BeginPlay() override;

private:
    FVector ShotDirection;
    AController* GetController() const;

    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    void DrawExplosionDebug(FVector Location);


};
