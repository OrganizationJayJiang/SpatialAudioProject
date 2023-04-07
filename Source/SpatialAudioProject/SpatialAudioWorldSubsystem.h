// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "FMODBlueprintStatics.h"
#include "SpatialAudioWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class SPATIALAUDIOPROJECT_API USpatialAudioWorldSubsystem : public UWorldSubsystem, public FTickableGameObject
{
	GENERATED_BODY()
private:
	FMOD::System* System;
	FMOD::DSP* Dsp;
	FMOD::Sound* Sound;
	FMOD::ChannelGroup* ChannelGroup;
	FMOD::Studio::EventDescription* EventDescription;
	FMOD::Studio::EventInstance* Instance;
	FMOD_RESULT result;
	

#pragma region override function
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override { return true; }
	virtual TStatId GetStatId() const override { return Super::GetStatID(); }
#pragma endregion

	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpatialAudio")
		FFMODEventInstance EventInstance;

	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="InEvent"></param>
	UFUNCTION(BlueprintCallable, Category = "SpatialAudio")
	void PlaySound(UFMODEvent* InEvent);

	/// <summary>
	/// ����FMOD�ռ仯���Ļ�ϸ߶�
	/// </summary>
	/// <param name="PanHeight"></param>
	UFUNCTION(BlueprintCallable, Category = "SpatialAudio")
	void SetPanHeight(float PanHeight);

	/// <summary>
	/// ����Channel�ķ�ʽʵ�ֿռ���Ƶ
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "SpatialAudio")
	void SpatialAudioChannelBasedApproach();

	/// <summary>
	/// ���ڶ���ķ�ʽʵ�ֿռ���Ƶ
	/// </summary>
	UFUNCTION(BlueprintCallable, Category = "SpatialAudio")
	void SpatialAudioObjectBasedApproach();
};
