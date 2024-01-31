// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoginPlayerController.generated.h"

class ULoginPanel;
/**
 * 
 */
UCLASS()
class CLIENT_API ALoginPlayerController : public APlayerController
{
	GENERATED_BODY()

	ALoginPlayerController();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget")
	TSubclassOf<ULoginPanel> LoginWidgetClass;

private:
	TObjectPtr<ULoginPanel> LoginWidget;

	UFUNCTION()
	void BindLoginRequest(const FText& ID, const FText& Password);
};
