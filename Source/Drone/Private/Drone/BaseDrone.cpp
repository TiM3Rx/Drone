#include "Drone/BaseDrone.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "HealthComponent.h"
#include "Weapon/Projectile.h"

ABaseDrone::ABaseDrone()
{
    PrimaryActorTick.bCanEverTick = true;

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
    BoxCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
    SetRootComponent(BoxCollision);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(GetRootComponent());
    CameraComponent->bUsePawnControlRotation = true;

    BoxMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh1"));
    BoxMesh1->SetupAttachment(GetRootComponent());

    BoxMesh2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh2"));
    BoxMesh2->SetupAttachment(GetRootComponent());

    BoxMesh3 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh3"));
    BoxMesh3->SetupAttachment(GetRootComponent());

    HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health"));

    bIsMoving = false;
}

void ABaseDrone::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
            ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(InputMappingContext, 0);
        }
    }

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &ABaseDrone::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ABaseDrone::OnHealthChanged);
}

void ABaseDrone::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    UpdateSpeed(DeltaTime);

    if (!CurrentVelocity.IsNearlyZero())
    {
        AddActorWorldOffset(CurrentVelocity * DeltaTime, true);
    }

    DebugShowCurrentSpeed();
}

void ABaseDrone::DebugShowCurrentSpeed()
{
    if (bShowCurrentSpeed)
    {
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(
                -1, 0.1f, FColor::Yellow,
                FString::Printf(TEXT("Speed: %.2f, Velocity: %s"),
                DroneSpeed,
                *CurrentVelocity.ToString()));
        }
    }
}

void ABaseDrone::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABaseDrone::Move);
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABaseDrone::Look);
        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &ABaseDrone::StartShooting);
        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &ABaseDrone::StopShooting);
    }
}

void ABaseDrone::Move(const FInputActionValue& Value)
{
    FVector InputVector = Value.Get<FVector>();

    if (!InputVector.IsNearlyZero())
    {
        CurrentVelocity += (GetActorForwardVector() * InputVector.Y +
            GetActorRightVector() * InputVector.X +
            GetActorUpVector() * InputVector.Z) *
            DroneAcceleration;
        bIsMoving = true;
    }
    else
    {
        bIsMoving = false;
    }
}

void ABaseDrone::Look(const FInputActionValue& Value)
{
    FVector2D LookAxisVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        AddControllerYawInput(LookAxisVector.X);
        AddControllerPitchInput(-LookAxisVector.Y);
    }
}

void ABaseDrone::UpdateSpeed(float DeltaSeconds)
{
    if (!CurrentVelocity.IsNearlyZero())
    {
        FVector Drag = -CurrentVelocity.GetSafeNormal() * DragCoefficient;
        CurrentVelocity += Drag * DeltaSeconds;

        if (CurrentVelocity.Size() < 10.0f)
        {
            CurrentVelocity = FVector::ZeroVector;
        }
    }

    DroneSpeed = CurrentVelocity.Size();
}

void ABaseDrone::OnDeath()
{
    SetLifeSpan(3.0f);
    UE_LOG(LogTemp, Display, TEXT("Player is Dead"));
}

void ABaseDrone::OnHealthChanged(float Health, float HealthDelta)
{
    UE_LOG(LogTemp, Display, TEXT("Health Was Changed"));
}

void ABaseDrone::StartShooting()
{
    if (!GetWorld()->GetTimerManager().IsTimerActive(FireTimerHandle))
    {
        SpawnProjectile();
        GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ABaseDrone::SpawnProjectile, FireRate, true);
    }
}

void ABaseDrone::StopShooting()
{
    GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}

void ABaseDrone::SpawnProjectile()
{
    if (!GetWorld() || Bullets <= 0) return;

    FVector Direction = GetActorForwardVector();
    FTransform SpawnTransform(FRotator::ZeroRotator, GetActorLocation() + (Direction * 100));

    AProjectile* Projectile = GetWorld()->SpawnActorDeferred<AProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(this);
        Projectile->FinishSpawning(SpawnTransform);
    }

    DecreaseAmmo();
}

void ABaseDrone::DecreaseAmmo()
{
    if (Bullets <= 0) return;

    Bullets--;
    UE_LOG(LogTemp, Display, TEXT("Ammo left: %i"), Bullets);

    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 0.1f, FColor::Red, FString::Printf(TEXT("Ammo: %i"), Bullets));
    }

    if (Bullets <= 0)
    {
        StopShooting();
    }
}

float ABaseDrone::GetDroneSpeed()
{
    return DroneSpeed;
}

float ABaseDrone::GetDroneMaxSpeed()
{
    return DroneMaxSpeed;
}

float ABaseDrone::GetDroneAcceleration()
{
    return DroneAcceleration;
}