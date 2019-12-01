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

#include "NightSky.h"

typedef struct {
	A_u_long	index;
	A_char		str[256];
} TableString;



TableString		g_strs[StrID_NUMTYPES] = {
	StrID_Name,						"Night Sky",
	StrID_Description,				"Generate a night sky quickly",
	StrID_Preset_Param_Name,			"Preset",
	StrID_Num_Stars_Param_Name,			"Number of Stars",
	StrID_Size_Param_Name,			"Size",
	StrID_Size_Random_Param_Name,			"Size Random",
	StrID_Glow_Intensity_Param_Name,			"Glow Intensity",
	StrID_Glow_Radius_Param_Name,			"Glow Radius",
	StrID_Random_Seed_Param_Name,			"Random Seed",
	StrID_Flicker_Param_Name,			"Flicker",
	StrID_Enabled_Param_Name,			"Enabled",
	StrID_Speed_Param_Name,			"Speed",
	StrID_Amount_Param_Name,			"Amount",
	StrID_Colour_Random_Param_Name,			"Colour Random",
	StrID_Colour_Controls_Param_Name,			"Colour Controls",
	StrID_Colour1_Enabled_Param_Name,			"Colour 1 Enabled",
	StrID_Colour1_Param_Name,			"Color 1",
	StrID_Colour2_Enabled_Param_Name,			"Color 2 Enabled",
	StrID_Colour2_Param_Name,			"Color 2",
	StrID_Colour3_Enabled_Param_Name,			"Color 3 Enabled",
	StrID_Colour3_Param_Name,			"Color 3",
	StrID_Colour4_Enabled_Param_Name,			"Color 4 Enabled",
	StrID_Colour4_Param_Name,			"Color 4",
	StrID_Colour5_Enabled_Param_Name,			"Color 5 Enabled",
	StrID_Colour5_Param_Name,			"Color 5"
};


char	*GetStringPtr(int strNum)
{
	return g_strs[strNum].str;
}
	