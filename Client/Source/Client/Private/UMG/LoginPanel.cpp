// Fill out your copyright notice in the Description page of Project Settings.


#include "UMG/LoginPanel.h"
#include "UMG/LabeledInput.h"
#include "Components/Button.h"

void ULoginPanel::NativePreConstruct()
{
	Super::NativePreConstruct();
	if (IsValid(LoginButton) && !BoundLogin)
	{
		LoginButton->OnClicked.AddDynamic(this, &ULoginPanel::BindLoginClicked);
		BoundLogin = true;
	}
}

void ULoginPanel::BindLoginClicked()
{
	const FText ID = IdWidget->GetValue();
	const FText Password = PasswordWidget->GetValue();

	OnLoginRequested.Broadcast(ID, Password);
}
