/*******************************************************************/
/*                                                                 */
/*                      ADOBE CONFIDENTIAL                         */
/*                   _ _ _ _ _ _ _ _ _ _ _ _ _                     */
/*                                                                 */
/* Copyright 2007 Adobe Systems Incorporated                       */
/* All Rights Reserved.                                            */
/*                                                                 */
/* NOTICE:  All information contained herein is, and remains the   */
/* property of Adobe Systems Incorporated and its suppliers, if    */
/* any.  The intellectual and technical concepts contained         */
/* herein are proprietary to Adobe Systems Incorporated and its    */
/* suppliers and may be covered by U.S. and Foreign Patents,       */
/* patents in process, and are protected by trade secret or        */
/* copyright law.  Dissemination of this information or            */
/* reproduction of this material is strictly forbidden unless      */
/* prior written permission is obtained from Adobe Systems         */
/* Incorporated.                                                   */
/*                                                                 */
/*******************************************************************/

/*	Vignette.cpp	

	This is a compiling husk of a project. Fill it in with interesting
	pixel processing code.
	
	Revision History

	Version		Change													Engineer	Date
	=======		======													========	======
	1.0			(seemed like a good idea at the time)					bbb			6/1/2002

	1.0			Okay, I'm leaving the version at 1.0,					bbb			2/15/2006
				for obvious reasons; you're going to 
				copy these files directly! This is the
				first XCode version, though.

	1.0			Let's simplify this barebones sample					zal			11/11/2010

	1.0			Added new entry point									zal			9/18/2017

*/

#include "NightSky.h"

static PF_Err 
About (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	AEGP_SuiteHandler suites(in_data->pica_basicP);
	
	suites.ANSICallbacksSuite1()->sprintf(	out_data->return_msg,
											"%s v%d.%d\r%s",
											STR(StrID_Name), 
											MAJOR_VERSION, 
											MINOR_VERSION, 
											STR(StrID_Description));
	return PF_Err_NONE;
}

static PF_Err 
GlobalSetup (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	out_data->my_version = PF_VERSION(	MAJOR_VERSION, 
										MINOR_VERSION,
										BUG_VERSION, 
										STAGE_VERSION, 
										BUILD_VERSION);

	out_data->out_flags =  PF_OutFlag_DEEP_COLOR_AWARE;	// just 16bpc, not 32bpc
	
	return PF_Err_NONE;
}

static PF_Err 
ParamsSetup (	
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err		err		= PF_Err_NONE;
	PF_ParamDef	def;	

	AEFX_CLR_STRUCT(def);

	PF_ADD_POPUPX(	STR(StrID_Preset_Param_Name),
							2,
							2,
							"Custom|Standard",
							0,
							PRESET_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_FLOAT_SLIDERX(	STR(StrID_Num_Stars_Param_Name),
					0,
					100,
					0,
					100,
					100,
					PF_Precision_INTEGER,
					0,
					0,
					NUM_STARS_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_FLOAT_SLIDERX(STR(StrID_Size_Param_Name),
		0.0,
		50.0,
		0.0,
		50.0,
		50.0,
		PF_Precision_TENTHS,
		0,
		0,
		SIZE_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_FLOAT_SLIDERX(STR(StrID_Size_Random_Param_Name),
		0.0,
		50.0,
		0.0,
		50.0,
		50.0,
		PF_Precision_TENTHS,
		0,
		0,
		SIZE_RANDOM_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_FLOAT_SLIDERX(STR(StrID_Glow_Intensity_Param_Name),
		0.0,
		100.0,
		0.0,
		100.0,
		50.0,
		PF_Precision_TENTHS,
		0,
		0,
		GLOW_INTENSITY_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_FLOAT_SLIDERX(STR(StrID_Glow_Radius_Param_Name),
		0.0,
		100.0,
		0.0,
		100.0,
		50.0,
		PF_Precision_TENTHS,
		0,
		0,
		GLOW_RADIUS_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_FLOAT_SLIDERX(STR(StrID_Random_Seed_Param_Name),
		1,
		9999,
		1,
		9999,
		9999,
		PF_Precision_INTEGER,
		0,
		0,
		RANDOM_SEED_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_TOPIC(STR(StrID_Flicker_Param_Name),
		FLICKER_START_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_CHECKBOXX(STR(StrID_Enabled_Param_Name),
		0,
		0,
		ENABLED_DISK_ID);

	PF_ADD_FLOAT_SLIDERX(STR(StrID_Speed_Param_Name),
		0.0,
		100.0,
		0.0,
		100.0,
		10.0,
		PF_Precision_TENTHS,
		0,
		0,
		SPEED_DISK_ID);

	PF_ADD_FLOAT_SLIDERX(STR(StrID_Amount_Param_Name),
		0.0,
		100.0,
		0.0,
		100.0,
		20.0,
		PF_Precision_TENTHS,
		0,
		0,
		AMOUNT_DISK_ID);

	PF_ADD_CHECKBOXX(STR(StrID_Colour_Random_Param_Name),
		0,
		0,
		COLOUR_RANDOM_DISK_ID);

	PF_END_TOPIC(FLICKER_END_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_TOPIC(STR(StrID_Colour_Controls_Param_Name),
		COLOUR_CONTROLS_START_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_CHECKBOXX(STR(StrID_Colour1_Enabled_Param_Name),
		1,
		0,
		COLOUR1_ENABLED_DISK_ID);

	PF_ADD_COLOR(STR(StrID_Colour1_Param_Name),
		255,
		126,
		126,
		COLOUR1_DISK_ID);

	PF_ADD_CHECKBOXX(STR(StrID_Colour2_Enabled_Param_Name),
		1,
		0,
		COLOUR2_ENABLED_DISK_ID);

	PF_ADD_COLOR(STR(StrID_Colour2_Param_Name),
		255,
		202,
		138,
		COLOUR2_DISK_ID);

	PF_ADD_CHECKBOXX(STR(StrID_Colour3_Enabled_Param_Name),
		1,
		0,
		COLOUR3_ENABLED_DISK_ID);

	PF_ADD_COLOR(STR(StrID_Colour3_Param_Name),
		99,
		137,
		255,
		COLOUR3_DISK_ID);

	PF_ADD_CHECKBOXX(STR(StrID_Colour4_Enabled_Param_Name),
		0,
		0,
		COLOUR4_ENABLED_DISK_ID);

	PF_ADD_COLOR(STR(StrID_Colour4_Param_Name),
		200,
		213,
		255,
		COLOUR4_DISK_ID);

	PF_ADD_CHECKBOXX(STR(StrID_Colour5_Enabled_Param_Name),
		0,
		0,
		COLOUR5_ENABLED_DISK_ID);

	PF_ADD_COLOR(STR(StrID_Colour5_Param_Name),
		255,
		255,
		255,
		COLOUR5_DISK_ID);

	PF_END_TOPIC(COLOUR_CONTROLS_END_DISK_ID);
	
	out_data->num_params = NIGHTSKY_NUM_PARAMS;

	return err;
}

static PF_Err
MySimpleGainFunc16 (
	void		*refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel16	*inP, 
	PF_Pixel16	*outP)
{
	PF_Err		err = PF_Err_NONE;

	GainInfo	*giP	= reinterpret_cast<GainInfo*>(refcon);
	PF_FpLong	tempF	= 0;
					
	if (giP){
		tempF = giP->gainF * PF_MAX_CHAN16 / 100.0;
		if (tempF > PF_MAX_CHAN16){
			tempF = PF_MAX_CHAN16;
		};

		outP->alpha		=	inP->alpha;
		outP->red		=	MIN((inP->red	+ (A_u_char) tempF), PF_MAX_CHAN16);
		outP->green		=	MIN((inP->green	+ (A_u_char) tempF), PF_MAX_CHAN16);
		outP->blue		=	MIN((inP->blue	+ (A_u_char) tempF), PF_MAX_CHAN16);
	}

	return err;
}

static PF_Err
MySimpleGainFunc8 (
	void		*refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel8	*inP, 
	PF_Pixel8	*outP)
{
	PF_Err		err = PF_Err_NONE;

	GainInfo	*giP	= reinterpret_cast<GainInfo*>(refcon);
	PF_FpLong	tempF	= 0;
					
	if (giP){
		tempF = giP->gainF * PF_MAX_CHAN8 / 100.0;
		if (tempF > PF_MAX_CHAN8){
			tempF = PF_MAX_CHAN8;
		};

		outP->alpha		=	inP->alpha;
		outP->red		=	MIN((inP->red	+ (A_u_char) tempF), PF_MAX_CHAN8);
		outP->green		=	MIN((inP->green	+ (A_u_char) tempF), PF_MAX_CHAN8);
		outP->blue		=	MIN((inP->blue	+ (A_u_char) tempF), PF_MAX_CHAN8);
	}

	return err;
}

static PF_Err 
Render (
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output )
{
	PF_Err				err		= PF_Err_NONE;
	AEGP_SuiteHandler	suites(in_data->pica_basicP);

	/*	Put interesting code here. */
	GainInfo			giP;
	AEFX_CLR_STRUCT(giP);
	A_long				linesL	= 0;

	linesL 		= output->extent_hint.bottom - output->extent_hint.top;
	//giP.gainF 	= params[NIGHTSKY_NUM_STARS]->u.fs_d.value;
	
	if (PF_WORLD_IS_DEEP(output)){
		ERR(suites.Iterate16Suite1()->iterate(	in_data,
												0,								// progress base
												linesL,							// progress final
												&params[NIGHTSKY_INPUT]->u.ld,	// src 
												NULL,							// area - null for all pixels
												(void*)&giP,					// refcon - your custom data pointer
												MySimpleGainFunc16,				// pixel function pointer
												output));
	} else {
		ERR(suites.Iterate8Suite1()->iterate(	in_data,
												0,								// progress base
												linesL,							// progress final
												&params[NIGHTSKY_INPUT]->u.ld,	// src 
												NULL,							// area - null for all pixels
												(void*)&giP,					// refcon - your custom data pointer
												MySimpleGainFunc8,				// pixel function pointer
												output));	
	}

	return err;
}


extern "C" DllExport
PF_Err PluginDataEntryFunction(
	PF_PluginDataPtr inPtr,
	PF_PluginDataCB inPluginDataCallBackPtr,
	SPBasicSuite* inSPBasicSuitePtr,
	const char* inHostName,
	const char* inHostVersion)
{
	PF_Err result = PF_Err_INVALID_CALLBACK;

	result = PF_REGISTER_EFFECT(
		inPtr,
		inPluginDataCallBackPtr,
		"Night Sky", // Name
		"NT NightSky", // Match Name
		"NT Productions", // Category
		AE_RESERVED_INFO); // Reserved Info

	return result;
}


PF_Err
EffectMain(
	PF_Cmd			cmd,
	PF_InData		*in_data,
	PF_OutData		*out_data,
	PF_ParamDef		*params[],
	PF_LayerDef		*output,
	void			*extra)
{
	PF_Err		err = PF_Err_NONE;
	
	try {
		switch (cmd) {
			case PF_Cmd_ABOUT:

				err = About(in_data,
							out_data,
							params,
							output);
				break;
				
			case PF_Cmd_GLOBAL_SETUP:

				err = GlobalSetup(	in_data,
									out_data,
									params,
									output);
				break; 
				
			case PF_Cmd_PARAMS_SETUP:

				err = ParamsSetup(	in_data,
									out_data,
									params,
									output);
				break;
				
			case PF_Cmd_RENDER:

				err = Render(	in_data,
								out_data,
								params,
								output);
				break;
		}
	}
	catch(PF_Err &thrown_err){
		err = thrown_err;
	}
	return err;
}

