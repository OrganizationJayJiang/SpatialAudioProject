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
	//��������
	EventInstance = UFMODBlueprintStatics::PlayEvent2D(GetWorld(), InEvent, true);

	Instance = EventInstance.Instance;
	//��ȡFMOD System
	FMOD::Studio::System* StudioSystem = IFMODStudioModule::Get().GetStudioSystem(EFMODSystemContext::Runtime);
	StudioSystem->getCoreSystem(&System);
	result = StudioSystem->flushCommands();

	//��ȡEventDescription
	Instance->getDescription(&EventDescription);
}

void USpatialAudioWorldSubsystem::SetPanHeight(float PanHeight)
{
	//��PanHeight��ֵԼ����-1.0f��1.0f
	PanHeight = FMath::Clamp(PanHeight, -1.0f, 1.0f);
	
	Dsp->setParameterFloat(FMOD_DSP_PAN_2D_HEIGHT_BLEND, PanHeight);
}

void USpatialAudioWorldSubsystem::SpatialAudioChannelBasedApproach()
{
	//����������ģʽΪ7.1.4 
	System->setSoftwareFormat(0, FMOD_SPEAKERMODE_7POINT1POINT4, 0);
	//ѡ���ܹ�����7.1.4���ݵ����ģʽ
	System->setOutput(FMOD_OUTPUTTYPE_WINSONIC);

	//�����ռ仯��
	System->createDSPByType(FMOD_DSP_TYPE_PAN, &Dsp);

	if (result == FMOD_OK)
	{
		//��ȡChannelGroup
		EventInstance.Instance->getChannelGroup(&ChannelGroup);
		//���ռ仯����dsp��ӵ�ChannelGroup��
		ChannelGroup->addDSP(0, Dsp);
	}
}

void USpatialAudioWorldSubsystem::SpatialAudioObjectBasedApproach()
{
	//��FMOD::System����Ϊһ��object ready output plugin
	System->setOutput(FMOD_OUTPUTTYPE_AUDIO3D);

	//����һ��object spatializer
	System->createDSPByType(FMOD_DSP_TYPE_OBJECTPAN, &Dsp);

	//�ṩ3Dλ����Ϣ
	FMOD_DSP_PARAMETER_3DATTRIBUTES attributes = { 0 };
	Dsp->setParameterData(FMOD_DSP_OBJECTPAN_3D_POSITION, &attributes, sizeof(attributes));

	if (result == FMOD_OK)
	{
		//��ȡChannelGroup
		EventInstance.Instance->getChannelGroup(&ChannelGroup);
		//���ռ仯����dsp��ӵ�ChannelGroup��
		ChannelGroup->addDSP(0, Dsp);
	}
}
