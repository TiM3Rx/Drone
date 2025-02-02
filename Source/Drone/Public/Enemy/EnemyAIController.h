#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class UEnemyAIPerceptionComponent;

UCLASS()
class DRONE_API AEnemyAIController : public AAIController
{
    GENERATED_BODY()
public:
    AEnemyAIController();
    FVector GetPlayerLocation();

    AActor* GetFocusedActor();
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UEnemyAIPerceptionComponent* EnemyAIPerceptionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "PlayerActor";

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;

};
