// Fill out your copyright notice in the Description page of Project Settings.


#include "SpatialAudioWorldSubsystem.h"
#include "FMODBlueprintStatics.h"
#include <fmod_studio.hpp>
#include <FMODStudioModule.h>

void USpatialAudioWorldSubsystem::Tick(float DeltaTime)
{
}
void USpatialAudioWorldSubsystem::PlaySound(UFMODEvent* InEvent)
{
	//播放声音
	EventInstance = UFMODBlueprintStatics::PlayEvent2D(GetWorld(), InEvent, true);

	Instance = EventInstance.Instance;
	//获取FMOD System
	FMOD::Studio::System* StudioSystem = IFMODStudioModule::Get().GetStudioSystem(EFMODSystemContext::Runtime);
	StudioSystem->getCoreSystem(&System);
	result = StudioSystem->flushCommands();

	//获取EventDescription
	Instance->getDescription(&EventDescription);
}

void USpatialAudioWorldSubsystem::SetPanHeight(float PanHeight)
{
	//将PanHeight的值约束在-1.0f到1.0f
	PanHeight = FMath::Clamp(PanHeight, -1.0f, 1.0f);
	
	Dsp->setParameterFloat(FMOD_DSP_PAN_2D_HEIGHT_BLEND, PanHeight);
}

void USpatialAudioWorldSubsystem::SpatialAudioChannelBasedApproach()
{
	//设置扬声器模式为7.1.4 
	System->setSoftwareFormat(0, FMOD_SPEAKERMODE_7POINT1POINT4, 0);
	//选择能够呈现7.1.4内容的输出模式
	System->setOutput(FMOD_OUTPUTTYPE_WINSONIC);

	//创建空间化器
	System->createDSPByType(FMOD_DSP_TYPE_PAN, &Dsp);

	if (result == FMOD_OK)
	{
		//获取ChannelGroup
		EventInstance.Instance->getChannelGroup(&ChannelGroup);
		//将空间化器的dsp添加到ChannelGroup中
		ChannelGroup->addDSP(0, Dsp);
	}
}

void USpatialAudioWorldSubsystem::SpatialAudioObjectBasedApproach()
{
	//将FMOD::System设置为一个object ready output plugin
	System->setOutput(FMOD_OUTPUTTYPE_AUDIO3D);

	//创建一个object spatializer
	System->createDSPByType(FMOD_DSP_TYPE_OBJECTPAN, &Dsp);

	//提供3D位置信息
	FMOD_DSP_PARAMETER_3DATTRIBUTES attributes = { 0 };
	Dsp->setParameterData(FMOD_DSP_OBJECTPAN_3D_POSITION, &attributes, sizeof(attributes));

	if (result == FMOD_OK)
	{
		//获取ChannelGroup
		EventInstance.Instance->getChannelGroup(&ChannelGroup);
		//将空间化器的dsp添加到ChannelGroup中
		ChannelGroup->addDSP(0, Dsp);
	}
}
