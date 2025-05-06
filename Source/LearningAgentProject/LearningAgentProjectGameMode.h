// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LearningAgentProjectGameMode.generated.h"

UCLASS(minimalapi)
class ALearningAgentProjectGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:

protected:
	UFUNCTION(BlueprintCallable)
	void WriteStringToFile(FString filePath, FString str);
	UFUNCTION(BlueprintCallable)
	FString ReadStringFromFile(FString filePath);

	void WriteStringToJsonFile(FString filePath, FString str);
	FString ReadStringFromJsonFile(FString filePath);
public:
	ALearningAgentProjectGameMode();

};



