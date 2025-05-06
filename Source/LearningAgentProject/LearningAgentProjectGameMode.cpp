// Copyright Epic Games, Inc. All Rights Reserved.

#include "LearningAgentProjectGameMode.h"
#include "LearningAgentProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "HAL/PlatformFileManager.h"
#include "Misc/FileHelper.h"
#include "Serialization/JsonSerializer.h"

void ALearningAgentProjectGameMode::WriteStringToFile(FString filePath, FString str)
{
	if (FFileHelper::SaveStringToFile(str, *filePath)) {
		//string wrote down to the file
		return;
	}
}

FString ALearningAgentProjectGameMode::ReadStringFromFile(FString filePath)
{
	if (FPlatformFileManager::Get().GetPlatformFile().FileExists(*filePath)) {
		//file found
		FString stringReadFromFile = "";
		if (!FFileHelper::LoadFileToString(stringReadFromFile, *filePath)) {
			//file loaded to string
		}
		
		else {
			//file couldn't find
		}
		return stringReadFromFile;
	}

	else {
		//file couldn't find
		return "";
	}
}

void ALearningAgentProjectGameMode::WriteStringToJsonFile(FString filePath, FString str)
{
}

FString ALearningAgentProjectGameMode::ReadStringFromJsonFile(FString filePath)
{
	return FString();
}

ALearningAgentProjectGameMode::ALearningAgentProjectGameMode() {
}
