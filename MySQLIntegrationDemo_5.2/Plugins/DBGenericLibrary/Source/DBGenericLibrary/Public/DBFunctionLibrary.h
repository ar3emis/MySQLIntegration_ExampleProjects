// Copyright 2019-2023, Athian Games. All Rights Reserved. 

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DBFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class DBGENERICLIBRARY_API UDBFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category="FileDialogue")
	static bool GetOpenFileDialogue(TArray<FString>& FileNames, FString DialogueTitle, FString FileTypes, bool multiselect);
};
