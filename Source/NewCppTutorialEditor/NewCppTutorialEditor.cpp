#include "NewCppTutorialEditor.h"
#include "Modules/ModuleManager.h"
#include "Modules/moduleInterface.h"

IMPLEMENT_GAME_MODULE(FNewCppTutorialEditorModule, NewCppTutorialEditor)

void FNewCppTutorialEditorModule::StartupModule()
{
	// Check if editor is valid
	if (GUnrealEd) {
		// Register the movevisualizer
		TSharedPtr<FMoveComponentVisualizer> MoveVisualizer = MakeShareable(new FMoveComponentVisualizer());

		if (MoveVisualizer.IsValid()) {
			GUnrealEd->RegisterComponentVisualizer(UMoveComponent::StaticClass()->GetFName(), MoveVisualizer);
			MoveVisualizer->OnRegister();
		}
	}
}

void FNewCppTutorialEditorModule::ShutdownModule()
{
	if (GUnrealEd) {
		GUnrealEd->UnregisterComponentVisualizer(UMoveComponent::StaticClass()->GetFName());
	}
}