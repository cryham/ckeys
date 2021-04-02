#include "Settings.h"

const rgb
Settings::clrKC[KC_Layer][3] =
{	// [rect,frame,text]
	{{ 26, 51, 77},{ 51,102,153},{179,217,254}},  // normal cyan
	{{ 77,115,153},{204,235,255},{227,242,255}},  // pressed cyan
	{{ 77, 51, 27},{142,112, 83},{234,167,154}},  // missing orange
	{{  2, 40, 90},{ 13,112,202},{ 44,180,255}},  // display blue
//	{{105,115,163},{225,235,255},{222,242,255}},  // viol blue
//	{{ 45, 41,107},{112,102,193},{227,217,254}},
},
Settings::clrLay[Lmax][3] =
{
	{{ 26, 77, 77},{ 51,152,153},{132,174,214}},  // L0- cyan (default, scan)
	{{  2, 40, 90},{ 13,112,202},{ 44,180,255}},  // L1- blue (off, display)
	{{ 22, 65, 22},{ 81,153, 73},{132,255,100}},  // L2+ green   162,255,154
	{{ 55, 55, 11},{133,133, 63},{240,240,100}},  // L3+ yellow	 240,240,125
	{{ 77, 51, 11},{142,112, 63},{244,167,114}},  // L4~ orange
	{{ 91, 35, 35},{173, 73, 73},{255,100,100}},  // L5` red
	{{ 72, 35, 72},{143, 93,143},{245,110,244}},  // L6` pink
	{{ 55, 25, 91},{113, 83,163},{150,110,255}},  // L7` violet
	{{ 35, 35, 91},{ 73, 73,183},{150,150,255}},  // L8` blue
},
Settings::clrOver = {220,230,240};  // mouse over frame

const rgb* Settings::getC(const KClr& kc, const int& lay, const int& rft)
{
	if (kc == KC_Layer)
		return &clrLay[lay][rft];

	return kc == KC_Lnum ?
		&clrLay[lay][rft] :
		&clrKC[kc][rft];
}
