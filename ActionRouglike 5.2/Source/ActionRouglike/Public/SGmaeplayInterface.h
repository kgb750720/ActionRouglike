// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SGmaeplayInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USGmaeplayInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ACTIONROUGLIKE_API ISGmaeplayInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void Interact(APawn *InstigatorPawn);
};
