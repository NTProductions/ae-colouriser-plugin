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

// OOOOOH WEEEEE123

// SOME MORE COMMENTS BRO

#include "Colouriser.h"

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

	//  colour 1

	AEFX_CLR_STRUCT(def);

	PF_ADD_CHECKBOXX(STR(StrID_ColourOneParamOne),
		1,
		0,
		CONEPONE_DISK_ID);


	AEFX_CLR_STRUCT(def);

	PF_ADD_FLOAT_SLIDERX(STR(StrID_ColourOneParamTwo),
		0.0,
		1.0,
		0.0,
		1.0,
		.11,
		PF_Precision_HUNDREDTHS,
		0,
		0,
		CONEPTWO_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_COLOR(STR(StrID_ColourOneParamThree),
		0,
		0,
		0,
		CONEPTHREE_DISK_ID);

	// colour 2

	AEFX_CLR_STRUCT(def);

	PF_ADD_CHECKBOXX(STR(StrID_ColourTwoParamOne),
		1,
		0,
		CTWOPONE_DISK_ID);


	AEFX_CLR_STRUCT(def);

	PF_ADD_FLOAT_SLIDERX(STR(StrID_ColourTwoParamTwo),
		0.0,
		1.0,
		0.0,
		1.0,
		.44,
		PF_Precision_HUNDREDTHS,
		0,
		0,
		CTWOPTWO_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_COLOR(STR(StrID_ColourTwoParamThree),
		255,
		0,
		0,
		CTWOPTHREE_DISK_ID);

	// colour 3

	AEFX_CLR_STRUCT(def);

	PF_ADD_CHECKBOXX(STR(StrID_ColourThreeParamOne),
		1,
		0,
		CTHREEPONE_DISK_ID);


	AEFX_CLR_STRUCT(def);

	PF_ADD_FLOAT_SLIDERX(STR(StrID_ColourThreeParamTwo),
		0.0,
		1.0,
		0.0,
		1.0,
		.66,
		PF_Precision_HUNDREDTHS,
		0,
		0,
		CTHREEPTWO_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_COLOR(STR(StrID_ColourThreeParamThree),
		0,
		255,
		198,
		CTHREEPTHREE_DISK_ID);

	// colour 4

	AEFX_CLR_STRUCT(def);

	PF_ADD_CHECKBOXX(STR(StrID_ColourFourParamOne),
		1,
		0,
		CFOURPONE_DISK_ID);


	AEFX_CLR_STRUCT(def);

	PF_ADD_FLOAT_SLIDERX(STR(StrID_ColourFourParamTwo),
		0.0,
		1.0,
		0.0,
		1.0,
		.88,
		PF_Precision_HUNDREDTHS,
		0,
		0,
		CFOURPTWO_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_COLOR(STR(StrID_ColourFourParamThree),
		151,
		244,
		255,
		CFOURPTHREE_DISK_ID);

	// colour 5

	AEFX_CLR_STRUCT(def);

	PF_ADD_CHECKBOXX(STR(StrID_ColourFiveParamOne),
		1,
		0,
		CFIVEPONE_DISK_ID);


	AEFX_CLR_STRUCT(def);

	PF_ADD_FLOAT_SLIDERX(STR(StrID_ColourFiveParamTwo),
		0.0,
		1.0,
		0.0,
		1.0,
		.98,
		PF_Precision_HUNDREDTHS,
		0,
		0,
		CFIVEPTWO_DISK_ID);

	AEFX_CLR_STRUCT(def);

	PF_ADD_COLOR(STR(StrID_ColourFiveParamThree),
		PF_MAX_CHAN8,
		PF_MAX_CHAN8,
		PF_MAX_CHAN8,
		CFIVEPTHREE_DISK_ID);
	
	out_data->num_params = COLOURISER_NUM_PARAMS;

	return err;
}

static double calculate8BitLum(PF_Pixel8 inputPixel) {
	double sum = (inputPixel.red + inputPixel.blue + inputPixel.green) / 3 * 0.0039215686274509803921568627451;
	return sum;
}

static PF_Err
colourise8BPC (
	void		*refcon, 
	A_long		xL, 
	A_long		yL, 
	PF_Pixel8	*inP, 
	PF_Pixel8	*outP)
{
	PF_Err		err = PF_Err_NONE;

	GainInfo	*giP	= reinterpret_cast<GainInfo*>(refcon);
	double	colourOneEnabledInt = giP->colourOneEnabled;
	double	colourOneThreshold = giP->colourOneThreshold;
	PF_Pixel8	colourOneColour = giP->colourOneColour;

	double	colourTwoEnabledInt = giP->colourTwoEnabled;
	double	colourTwoThreshold = giP->colourTwoThreshold;
	PF_Pixel8	colourTwoColour = giP->colourTwoColour;

	double	colourThreeEnabledInt = giP->colourThreeEnabled;
	double	colourThreeThreshold = giP->colourThreeThreshold;
	PF_Pixel8	colourThreeColour = giP->colourThreeColour;

	double	colourFourEnabledInt = giP->colourFourEnabled;
	double	colourFourThreshold = giP->colourFourThreshold;
	PF_Pixel8	colourFourColour = giP->colourFourColour;

	double	colourFiveEnabledInt = giP->colourFiveEnabled;
	double	colourFiveThreshold = giP->colourFiveThreshold;
	PF_Pixel8	colourFiveColour = giP->colourFiveColour;

	double upperBound, lowerBound;
	double searchThreshold = .1;
	double tintPercent = .5;
	PF_FpLong alphaAmount = 255;
	PF_FpLong roundedVal;
					
	if (giP){
		// for now, we shall say that the threshold is a luminance between 0-threshold. This may make too many things detected, but for now it works, until I add another variable to add a threshold "range", for how far out form the threshold luminance to look for similar pixels
		if (colourOneEnabledInt == 1) {
			upperBound = colourOneThreshold + searchThreshold;
			lowerBound = colourOneThreshold - searchThreshold;
			if (calculate8BitLum(*inP) > lowerBound && calculate8BitLum(*inP) < upperBound) {
				roundedVal = inP->red + colourOneColour.red * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->red = roundedVal;
				roundedVal = inP->green + colourOneColour.green * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->green = roundedVal;
				roundedVal = inP->blue + colourOneColour.blue * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->blue = roundedVal;
				outP->alpha = alphaAmount;
		}
		}
		if (colourTwoEnabledInt == 1) {
			upperBound = colourTwoThreshold + searchThreshold;
			lowerBound = colourTwoThreshold - searchThreshold;
			if (calculate8BitLum(*inP) > lowerBound && calculate8BitLum(*inP) < upperBound) {
				roundedVal = inP->red + colourTwoColour.red * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->red = roundedVal;
				roundedVal = inP->green + colourTwoColour.green * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->green = roundedVal;
				roundedVal = inP->blue + colourTwoColour.blue * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->blue = roundedVal;
				outP->alpha = alphaAmount;
			}
		}
		if (colourThreeEnabledInt == 1) {
			upperBound = colourThreeThreshold + searchThreshold;
			lowerBound = colourThreeThreshold - searchThreshold;
			if (calculate8BitLum(*inP) > lowerBound && calculate8BitLum(*inP) < upperBound) {
				roundedVal = inP->red + colourThreeColour.red * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->red = roundedVal;
				roundedVal = inP->green + colourThreeColour.green * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->green = roundedVal;
				roundedVal = inP->blue + colourThreeColour.blue * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->blue = roundedVal;
				outP->alpha = alphaAmount;
			}
		}
		if (colourFourEnabledInt == 1) {
			upperBound = colourFourThreshold + searchThreshold;
			lowerBound = colourFourThreshold - searchThreshold;
			if (calculate8BitLum(*inP) > lowerBound && calculate8BitLum(*inP) < upperBound) {
				roundedVal = inP->red + colourFourColour.red * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->red = roundedVal;
				roundedVal = inP->green + colourFourColour.green * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->green = roundedVal;
				roundedVal = inP->blue + colourFourColour.blue * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->blue = roundedVal;
				outP->alpha = alphaAmount;
			}
		}
		if (colourFiveEnabledInt == 1) {
			upperBound = colourFiveThreshold + searchThreshold;
			lowerBound = colourFiveThreshold - searchThreshold;
			if (calculate8BitLum(*inP) > lowerBound && calculate8BitLum(*inP) < upperBound) {
				roundedVal = inP->red + colourFiveColour.red * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->red = roundedVal;
				roundedVal = inP->green + colourFiveColour.green * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->green = roundedVal;
				roundedVal = inP->blue + colourFiveColour.blue * tintPercent;
				if (roundedVal > 255) {
					roundedVal = 255;
				}
				outP->blue = roundedVal;
				outP->alpha = alphaAmount;
			}
		}

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
	giP.colourOneEnabled 	= params[COLOURISER_CONEPONE]->u.bd.value;
	giP.colourOneThreshold 	= params[COLOURISER_CONEPTWO]->u.fs_d.value;
	giP.colourOneColour 	= params[COLOURISER_CONEPTHREE]->u.cd.value;

	giP.colourTwoEnabled = params[COLOURISER_CTWOPONE]->u.bd.value;
	giP.colourTwoThreshold = params[COLOURISER_CTWOPTWO]->u.fs_d.value;
	giP.colourTwoColour = params[COLOURISER_CTWOPTHREE]->u.cd.value;

	giP.colourThreeEnabled = params[COLOURISER_CTHREEPONE]->u.bd.value;
	giP.colourThreeThreshold = params[COLOURISER_CTHREEPTWO]->u.fs_d.value;
	giP.colourThreeColour = params[COLOURISER_CTHREEPTHREE]->u.cd.value;

	giP.colourFourEnabled = params[COLOURISER_CFOURPONE]->u.bd.value;
	giP.colourFourThreshold = params[COLOURISER_CFOURPTWO]->u.fs_d.value;
	giP.colourFourColour = params[COLOURISER_CFOURPTHREE]->u.cd.value;

	giP.colourFiveEnabled = params[COLOURISER_CFIVEPONE]->u.bd.value;
	giP.colourFiveThreshold = params[COLOURISER_CFIVEPTWO]->u.fs_d.value;
	giP.colourFiveColour = params[COLOURISER_CFIVEPTHREE]->u.cd.value;

		ERR(suites.Iterate8Suite1()->iterate(	in_data,
												0,								// progress base
												output->height,							// progress final
												&params[COLOURISER_INPUT]->u.ld,	// src 
												NULL,							// area - null for all pixels
												(void*)&giP,					// refcon - your custom data pointer
			colourise8BPC,				// pixel function pointer
												output));	


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
		"Colouriser", // Name
		"NT Colouriser", // Match Name
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

