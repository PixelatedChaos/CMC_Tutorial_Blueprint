// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMNCharacterMovementComponent.h"
#include "CustomCharacterMovementComponent.generated.h"


USTRUCT(BlueprintType)
struct FMovementProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	float CustomMaxSpeed = 600;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	float CustomMaxAcceleration = 2048.0f;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	float CustomMaxDeceleration = 2048.0f;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	float CustomBrakingFriction = 8.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	float CustomGravityScale = 4.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	float CustomAirControl = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	float CustomJumpForce = 1200.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	TEnumAsByte<enum EMovementMode> DesiredMovementMode;
};

/**
 * 
 */
UCLASS()
class CMCTUTORIALBP_API UCustomCharacterMovementComponent : public USMN_CharacterMovementComponent
{
	GENERATED_BODY()

public:

	UCustomCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);

	

	/**
	*We follow a similar pattern to SMN2 here, adding K2 nodes to allow us to easily reimplement these core CMC functions in BP.
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "SMN2", meta = (DisplayName = "StartNewPhysics"))
	void K2_StartNewPhysics(float deltaTime, int32 Iterations);
	virtual void K2_StartNewPhysics_Implementation(float deltaTime, int32 Iterations);
	virtual void StartNewPhysics(float deltaTime, int32 Iterations) override;

	//Important for overriding jump functionality.
	UFUNCTION(BlueprintNativeEvent, Category = "SMN2", meta = (DisplayName = "DoJump"))
	bool K2_DoJump(bool bReplayingMoves);
	virtual bool K2_DoJump_Implementation(bool bReplayingMoves);
	virtual bool DoJump(bool bReplayingMoves) override;

	

#pragma region Movement Profiles

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	bool bUseMovementProfiles;

	//Custom variables
	/**
	* We are doing a full BP impolementation, so these values are used in overridden functions in BP. 
	* View K2_GetMaxSpeed, K2_GetMaxAcceleration, etc inside of BP_CustomCMC to see how we use these values in our project.
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	float CustomMaxSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	float CustomMaxAcceleration;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	float CustomMaxDeceleration;

	//Set our custom profile, plus allow BP to extend it if necessary.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement Profiles")
	void SetCurrentMovementProfile(FMovementProfile NewProfile);
	virtual void SetCurrentMovementProfile_Implementation(FMovementProfile NewProfile);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	FMovementProfile DefaultMovementProfile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement Profiles")
	FMovementProfile CurrentMovementProfile;

#pragma endregion

protected:

	/** 
	* Scale input acceleration, based on movement acceleration rate. 
	* !! Make acceleration changes here for replication !!
	*/
	UFUNCTION(BlueprintNativeEvent, Category = "SMN2", meta = (DisplayName = "ScaleInputAcceleration"))
	FVector K2_ScaleInputAcceleration(const FVector& InputAcceleration) const;

	/** Scale input acceleration, based on movement acceleration rate.*/
	virtual FVector ScaleInputAcceleration(const FVector& InputAcceleration) const override;
};
