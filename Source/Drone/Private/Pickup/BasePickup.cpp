#include "Pickup/BasePickup.h"
#include "Components/SphereComponent.h"
#include "Drone/BaseDrone.h"

ABasePickup::ABasePickup()
{
    PrimaryActorTick.bCanEverTick = true;
    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->InitSphereRadius(50.0f);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(SphereComponent);

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(GetRootComponent());
    MeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
}

void ABasePickup::BeginPlay()
{
    Super::BeginPlay();

    check(SphereComponent);
    check(MeshComponent);
}

void ABasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<ABaseDrone>(OtherActor);
    if (!Pawn)return;
    if (GivePickupTo(Pawn))
    {
        Destroy();
    }
}

bool ABasePickup::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}


void ABasePickup::Respawn()
{
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true, true);
    }
    GetWorldTimerManager().ClearTimer(RespawnTimerHandle);
}

void ABasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

