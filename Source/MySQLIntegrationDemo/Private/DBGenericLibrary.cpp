// Fill out your copyright notice in the Description page of Project Settings.


#include "DBGenericLibrary.h"

typedef char*(*_OpenFileDialogue)(char* DialogueTitle, char* FileTypes, bool multiselect);
_OpenFileDialogue m_OpenFileDialogueFromDll;

static void *v_dllHandle;

static FString GetFilePath(FString DLLName)
{
	FString ProjectPath = FPaths::ProjectDir();
	FString DllPath = FPaths::Combine(*ProjectPath, TEXT("Source/Libraries"), DLLName);

	if (FPaths::FileExists(DllPath))
	{
		return DllPath;
	}
	else
	{
		return "";
	}
	
}

bool LoadDLL(FString DLLName)
{
	FString DllPath = GetFilePath(DLLName);

	if (FPaths::FileExists(DllPath))
	{
		v_dllHandle = FPlatformProcess::GetDllHandle(*DllPath);
		if (v_dllHandle != nullptr)
		{
			return true;
		}
	}
	return false;
}

void UnLoadDLL()
{
	if (v_dllHandle != nullptr)
	{
		FPlatformProcess::FreeDllHandle(m_OpenFileDialogueFromDll);
		FPlatformProcess::FreeDllHandle(v_dllHandle);
		v_dllHandle = nullptr;
	}
}

template<typename T>
bool ImportMethod(FString methodname, T& method)
{
	if (v_dllHandle != nullptr)
	{
		method = static_cast<T>(FPlatformProcess::GetDllExport(v_dllHandle, *methodname));
		if (method)
		{
			return true;
		}
	}
	return false;

}

bool UDBGenericLibrary::GetOpenFileDialogue(TArray<FString>& FileNames, FString DialogueTitle, FString FileTypes, bool multiselect)
{
#if PLATFORM_WINDOWS
	if (LoadDLL("FileBrowser.dll"))
	{
		if (ImportMethod<_OpenFileDialogue>("OpenFileDialogue", m_OpenFileDialogueFromDll))
		{

			char* title = TCHAR_TO_ANSI(*DialogueTitle);
			char* filetypes = TCHAR_TO_ANSI(*FileTypes);

			char* openedfilename = m_OpenFileDialogueFromDll(title, filetypes, multiselect);

			FString RString = FString(openedfilename);
			if (!RString.IsEmpty())
			{
				FString LString;
				while (!RString.IsEmpty())
				{
					FString NString = RString;
					RString.Empty();
					if (NString.Contains(","))
					{
						NString.Split(",", &LString, &RString, ESearchCase::CaseSensitive);
					}
					else
					{
						LString = NString;
					}
					if (FPaths::FileExists(LString))
					{
						FileNames.Add(LString);
					}
				}
			}
		}

		
		if (FileNames.Num() > 0)
		{
			UnLoadDLL();
			return true;
		}

	}

	UnLoadDLL();

#endif

	return false;
}

