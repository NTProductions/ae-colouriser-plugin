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

#include "Colouriser.h"

typedef struct {
	A_u_long	index;
	A_char		str[256];
} TableString;



TableString		g_strs[StrID_NUMTYPES] = {
	StrID_Name,						"Colouriser",
	StrID_Description,				"Add colour to your B&W imagery",
	StrID_ColourOneParamOne,  "Colour 1",
	StrID_ColourOneParamTwo,  "Colour 1 Threshold",
	StrID_ColourOneParamThree,  "",

	StrID_ColourTwoParamOne,  "Colour 2",
	StrID_ColourTwoParamTwo,  "Colour 2 Threshold",
	StrID_ColourTwoParamThree,  "",

	StrID_ColourThreeParamOne,  "Colour 3",
	StrID_ColourThreeParamTwo,  "Colour 3 Threshold",
	StrID_ColourThreeParamThree,  "",

	StrID_ColourFourParamOne,  "Colour 4",
	StrID_ColourFourParamTwo,  "Colour 4 Threshold",
	StrID_ColourFourParamThree,  "",

	StrID_ColourFiveParamOne,  "Colour 5",
	StrID_ColourFiveParamTwo,  "Colour 5 Threshold",
	StrID_ColourFiveParamThree,  ""
	
};


char	*GetStringPtr(int strNum)
{
	return g_strs[strNum].str;
}
	