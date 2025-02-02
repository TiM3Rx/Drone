#include "Enemy/Turret.h"
#include "HealthComponent.h"
#include "Drone/BaseDrone.h"
#include "Weapon/Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "Enemy/EnemyAIController.h"
#include "Enemy/EnemyAIPerceptionComponent.h"
#include "BrainComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ATurret::ATurret()
{
    PrimaryActorTick.bCanEverTick = true;

    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AEnemyAIController::StaticClass();
    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));
    bUseControllerRotationYaw = false;

    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 60.0f, 0.0f);
    }
}

void ATurret::BeginPlay()
{
    Super::BeginPlay();

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &ATurret::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ATurret::OnHealthChanged);

    /*AEnemyAIController* AIController = Cast<AEnemyAIController>(Controller);
    if (AIController && AIController->GetBlackboardComponent())
    {
        APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this, 0);
        if (PlayerPawn)
        {
            AIController->GetBlackboardComponent()->SetValueAsObject("PlayerActor", PlayerPawn);
        }
    }*/
}

void ATurret::OnDeath()
{
    const auto MyController = Cast<AEnemyAIController>(Controller);
    if (MyController && MyController->BrainComponent)
    {
        MyController->BrainComponent->Cleanup();
    }
    SetLifeSpan(0.1f);
}

void ATurret::OnHealthChanged(float Health, float HealthDelta)
{
    UE_LOG(LogTemp, Display, TEXT("Health Was Changed"));
}

void ATurret::Fire()
{
    if (!GetWorld())return;
    const auto MyController = Cast<AEnemyAIController>(Controller);
    if (!MyController)return;

    FVector Direction = (MyController->GetPlayerLocation() - (GetActorLocation() + (GetActorForwardVector() * 100))).GetSafeNormal();
    FTransform SpawnTransform(FRotator::ZeroRotator, GetActorLocation() + (GetActorForwardVector() * 100));

    AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
}

