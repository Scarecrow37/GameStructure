// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LabeledInput.generated.h"

class UEditableTextBox;
class UTextBlock;
/**
 * 
 */
UCLASS()
class CLIENT_API ULabeledInput : public UUserWidget
{
	GENERATED_BODY()

public:
	ULabeledInput(const FObjectInitializer& ObjectInitializer);
	
	UFUNCTION(BlueprintCallable)
	FText GetValue() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	UTextBlock* LabelWidget;
	
	UPROPERTY(EditDefaultsOnly, Category = "Widget", meta = (BindWidget))
	UEditableTextBox* ValueWidget;

	UPROPERTY(EditAnywhere, Category = "Slot")
	float SizeRatioOfLabelToValue;

	UPROPERTY(EditAnywhere, Category = "Content")
	FText Label;

	UPROPERTY(EditAnywhere, Category = "Content")
	FText Value;

	UPROPERTY(EditAnywhere, Category = "Content")
	FText Hint;

	UPROPERTY(EditAnywhere, Category = "Content")
	bool IsPassword;
	
	virtual void NativePreConstruct() override;

private:
	UFUNCTION()
	void OnChangedValue(const FText& Text);
};
