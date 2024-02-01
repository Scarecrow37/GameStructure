// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModes/LoginPlayerController.h"
#include "UMG/LoginPanel.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Interfaces/IPv4/IPv4Address.h"

ALoginPlayerController::ALoginPlayerController()
{
	SetShowMouseCursor(true);
	
}

void ALoginPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(LoginWidgetClass))
	{
		LoginWidget = TObjectPtr<ULoginPanel>(CreateWidget<ULoginPanel>(this, LoginWidgetClass, FName("LoginWidget")));
		if (IsValid(LoginWidget))
		{
			LoginWidget->OnLoginRequested.AddDynamic(this, &ALoginPlayerController::BindLoginRequest);
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(LoginWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			Super::SetInputMode(InputMode);
			LoginWidget->AddToViewport();
		}
	}
}

void ALoginPlayerController::BindLoginRequest(const FText& ID, const FText& Password)
{
	TSharedPtr<FSocket> Socket = MakeShareable(
		ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(TEXT("Stream"), TEXT("Client Socket")));
	FString AddressString = TEXT("127.0.0.1");
	FIPv4Address IP;
	FIPv4Address::Parse(AddressString, IP);
	 constexpr int32 Port = 12345;
	 const TSharedRef<FInternetAddr> Address = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	 Address->SetIp(IP.Value);
	 Address->SetPort(Port);
	
	 bool IsConnected = Socket->Connect(*Address);
	
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("%hhd"), IsConnected));
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("ID : %s / Password : %s"), *ID.ToString(), *Password.ToString()));
}
