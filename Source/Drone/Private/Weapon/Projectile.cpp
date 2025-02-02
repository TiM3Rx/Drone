#include "Weapon/Projectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AProjectile::AProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
    SphereComponent->InitSphereRadius(DamageRadius);
    SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    SphereComponent->bReturnMaterialOnMove = true;
    SetRootComponent(SphereComponent);

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
    FAttachmentTransformRules Rules(EAttachmentRule::KeepRelative, false);
    MeshComponent->AttachToComponent(SphereComponent, Rules);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;

}

void AProjectile::SetShotDirection(const FVector& Direction)
{
    ShotDirection = Direction;
}

void AProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    check(SphereComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    if (GetOwner())
    {
        SphereComponent->MoveIgnoreActors.Add(GetOwner());
        SphereComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    }
    SphereComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);
    SetLifeSpan(LifeSeconds);
}

AController* AProjectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld())
        return;
    FVector ExplosionLocation = GetActorLocation();

    DrawExplosionDebug(ExplosionLocation);

    MovementComponent->StopMovementImmediately();
    UGameplayStatics::ApplyPointDamage(OtherActor, DamageAmount, NormalImpulse, Hit, GetController(), this, UDamageType::StaticClass());
    Destroy();
}

void AProjectile::DrawExplosionDebug(FVector Location)
{
    if (!GetWorld()) return;

    DrawDebugSphere(
        GetWorld(),
        Location,
        DamageRadius,  
        12, 
        ExplosionColor,
        false, 
        ExplosionDuration
    );

}

