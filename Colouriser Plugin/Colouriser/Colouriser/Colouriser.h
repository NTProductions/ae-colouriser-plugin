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

/*
	Colouriser.h
*/

#pragma once

#ifndef COLOURISER_H
#define COLOURISER_H

typedef unsigned char		u_char;
typedef unsigned short		u_short;
typedef unsigned short		u_int16;
typedef unsigned long		u_long;
typedef short int			int16;
#define PF_TABLE_BITS	12
#define PF_TABLE_SZ_16	4096

#define PF_DEEP_COLOR_AWARE 1	// make sure we get 16bpc pixels; 
								// AE_Effect.h checks for this.

#include "AEConfig.h"

#ifdef AE_OS_WIN
	typedef unsigned short PixelType;
	#include <Windows.h>
#endif

#include "entry.h"
#include "AE_Effect.h"
#include "AE_EffectCB.h"
#include "AE_Macros.h"
#include "Param_Utils.h"
#include "AE_EffectCBSuites.h"
#include "String_Utils.h"
#include "AE_GeneralPlug.h"
#include "AEFX_ChannelDepthTpl.h"
#include "AEGP_SuiteHandler.h"

#include "Colouriser_Strings.h"

/* Versioning information */

#define	MAJOR_VERSION	1
#define	MINOR_VERSION	0
#define	BUG_VERSION		0
#define	STAGE_VERSION	PF_Stage_DEVELOP
#define	BUILD_VERSION	1

enum {
	COLOURISER_INPUT = 0,
	COLOURISER_CONEPONE,
	COLOURISER_CONEPTWO,
	COLOURISER_CONEPTHREE,
	COLOURISER_CTWOPONE,
	COLOURISER_CTWOPTWO,
	COLOURISER_CTWOPTHREE,
	COLOURISER_CTHREEPONE,
	COLOURISER_CTHREEPTWO,
	COLOURISER_CTHREEPTHREE,
	COLOURISER_CFOURPONE,
	COLOURISER_CFOURPTWO,
	COLOURISER_CFOURPTHREE,
	COLOURISER_CFIVEPONE,
	COLOURISER_CFIVEPTWO,
	COLOURISER_CFIVEPTHREE,
	COLOURISER_NUM_PARAMS
};

enum {
	CONEPONE_DISK_ID = 1,
	CONEPTWO_DISK_ID,
	CONEPTHREE_DISK_ID,
	CTWOPONE_DISK_ID,
	CTWOPTWO_DISK_ID,
	CTWOPTHREE_DISK_ID,
	CTHREEPONE_DISK_ID,
	CTHREEPTWO_DISK_ID,
	CTHREEPTHREE_DISK_ID,
	CFOURPONE_DISK_ID,
	CFOURPTWO_DISK_ID,
	CFOURPTHREE_DISK_ID,
	CFIVEPONE_DISK_ID,
	CFIVEPTWO_DISK_ID,
	CFIVEPTHREE_DISK_ID
};

typedef struct GainInfo{
	PF_FpLong	gainF;
} GainInfo, *GainInfoP, **GainInfoH;


extern "C" {

	DllExport
	PF_Err
	EffectMain(
		PF_Cmd			cmd,
		PF_InData		*in_data,
		PF_OutData		*out_data,
		PF_ParamDef		*params[],
		PF_LayerDef		*output,
		void			*extra);

}

#endif // COLOURISER_H