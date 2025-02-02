#include "Enemy/FindPlayerBTService.h"
#include "Enemy/EnemyAIPerceptionComponent.h"
#include "Enemy/EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

void UFindPlayerBTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto Component = Controller->GetComponentByClass(UEnemyAIPerceptionComponent::StaticClass());
        const auto PerceptionComponent = Cast<UEnemyAIPerceptionComponent>(Component);

        if (PerceptionComponent)
        {
            //Controller->GetBlackboardComponent()->SetValueAsObject("PlayerActor", PerceptionComponent->GetPlayerCharacter());
            Blackboard->SetValueAsObject(PlayerActorKey.SelectedKeyName, PerceptionComponent->GetPlayerCharacter());
            //UE_LOG(LogTemp, Warning, TEXT("%s: "), PerceptionComponent->GetPlayerCharacter());
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
