// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/LoginPlayerController.h"
#include "UMG/LoginPanel.h"

ALoginPlayerController::ALoginPlayerController()
{
	SetShowMouseCursor(true);
	if (IsValid(LoginWidgetClass))
	{
		LoginWidget = TObjectPtr<ULoginPanel>(CreateWidget<ULoginPanel>(this, LoginWidgetClass, FName("LoginWidget")));
		if (IsValid(LoginWidget))
		{
			LoginWidget->OnLoginRequested.AddDynamic(this, &ALoginPlayerController::BindLoginRequest);
			FInputModeUIOnly InputMode(LoginWidget, EMouseLockMode::DoNotLock);
			Super::SetInputMode(InputMode);
		}
	}
}

void ALoginPlayerController::BindLoginRequest(const FText& ID, const FText& Password)
{
	GEngine->AddOnScreenDebugMessage(-1, 0.5f, FColor::Red, FString::Printf(TEXT("ID : %s / Password : %s"), *ID.ToString(), *Password.ToString()));
}
