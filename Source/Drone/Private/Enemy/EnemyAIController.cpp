#include "Enemy/EnemyAIController.h"
#include "Enemy/Turret.h"
#include "Enemy/EnemyAIPerceptionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

AEnemyAIController::AEnemyAIController()
{
    EnemyAIPerceptionComponent = CreateDefaultSubobject<UEnemyAIPerceptionComponent>("MyAIPerseptionComponent");
    SetPerceptionComponent(*EnemyAIPerceptionComponent);
}

FVector AEnemyAIController::GetPlayerLocation()
{
    const auto AimActor = EnemyAIPerceptionComponent->GetPlayerCharacter();
    if (AimActor)
    {
        FVector AimVector = AimActor->GetActorLocation();
        return AimVector;
    }
    return FVector::ZeroVector;
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const auto AICharacter = Cast<ATurret>(InPawn);
    if (AICharacter)
    {
        RunBehaviorTree(AICharacter->BehaviorTreeAsset);
    }
}

void AEnemyAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    const auto AimActor = GetFocusedActor();
    if (AimActor)
    {
        SetFocus(AimActor);
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay);
    }
}

AActor* AEnemyAIController::GetFocusedActor()
{
    if (!GetBlackboardComponent())
        return nullptr;

    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
