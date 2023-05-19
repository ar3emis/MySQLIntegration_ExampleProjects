// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DBGenericLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MYSQLINTEGRATIONDEMO_API UDBGenericLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
* Opens the File Open Dialogue Window.
*
* @param FileNames  The array of filenames selected for openiong.
* @param DialogueTitle  The Title that appears in the titlebar of the File Open Dialogue window.
* @param FileTypes  The allowed FileTypes for the File Open Dialogue window.
* @param multiselect  If user can select multiple files.
*/
	UFUNCTION(BlueprintCallable, Category = "FIleBrowser")
		static bool GetOpenFileDialogue(TArray<FString>& FileNames, FString DialogueTitle, FString FileTypes,
			bool multiselect);
};

