#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePickup.generated.h"

class USphereComponent;

UCLASS()
class DRONE_API ABasePickup : public AActor
{
    GENERATED_BODY()

public:
    ABasePickup();

    virtual void Tick(float DeltaTime) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
    TObjectPtr<USphereComponent> SphereComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
    TObjectPtr<UStaticMeshComponent> MeshComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

    virtual void BeginPlay() override;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
    FTimerHandle RespawnTimerHandle;

    virtual bool GivePickupTo(APawn* PlayerPawn);
    void Respawn();
};
