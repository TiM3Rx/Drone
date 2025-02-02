#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseDrone.generated.h"

class UCameraComponent;
class UBoxComponent;
class UInputMappingContext; 
class UInputAction;
class UHealthComponent;
class AProjectile;

struct FInputActionValue; 

UCLASS()
class DRONE_API ABaseDrone : public APawn
{
    GENERATED_BODY()

public:
    ABaseDrone();

    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void SetAmmoData(int32 NewAmmoData)
    {
        Bullets += NewAmmoData;
    }
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UCameraComponent> CameraComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UStaticMeshComponent> BoxMesh1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UStaticMeshComponent> BoxMesh2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UStaticMeshComponent> BoxMesh3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UBoxComponent> BoxCollision;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UHealthComponent> HealthComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<UInputAction> MoveAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<UInputAction> LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr<UInputAction> ShootAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
    TObjectPtr <UInputMappingContext> InputMappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float DroneSpeed = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float DroneMaxSpeed = 25.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float DroneAcceleration = 6.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
    float DragCoefficient = 0.2f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
    TSubclassOf<AProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile")
    int32 Bullets = 10;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Projectile")
    float FireRate = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DEBUG")
    bool bShowCurrentSpeed = false;

    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void StartShooting();
    void StopShooting();

    void UpdateSpeed(float DeltaSeconds);

    void OnDeath();
    void OnHealthChanged(float Health, float HealthDelta);

    void SpawnProjectile();
    void DecreaseAmmo();

    float GetDroneSpeed();
    float GetDroneMaxSpeed();
    float GetDroneAcceleration();

    virtual void BeginPlay() override;

private:
    FVector CurrentVelocity;

    FTimerHandle FireTimerHandle;

    bool bIsMoving;

    void DebugShowCurrentSpeed();
};
