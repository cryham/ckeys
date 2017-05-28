#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include "App.h"
#include "Util.h"
using namespace std;  using namespace ImGui;  using namespace SFML;


//  Gui draw and process
///-----------------------------------------------------------------------------
void App::Gui()
{

	//  dimensions
	const static int h = 114, w1 = 185, w2 = 110, w3 = 130;

	//  window
	SetNextWindowPos( ImVec2(0, set.ywSize - h),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(set.xwSize, h), ImGuiSetCond_Always);

	bool open = true;
	const int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;

	Begin("Window", &open, flags);


	//---------------------------------------------
	bool e;  // edited, changed
	int x = 0, w;

	//  1st line  ----
	Sep(1);
	//w = w1;  e = /*Checkbox*/Text("Layers:", &set.bLayout);  x += w;  SameLine(x);
	w = w1;  Text("Layers:");  x += w;  SameLine(x);
	w = 60;  int r;
	const int Lnum = 3;
	bool* Lchk[Lnum] = {&set.bL1, &set.bL2, &set.bL3};
	const char* Lname[Lnum] = {"L1", "L2", "L3"};
	const ImVec4 Lclr[Lnum] = {
		ImVec4(0.3f, 0.6f, 1.0f, 1.f),
		ImVec4(0.4f, 0.85f, 0.2f, 1.f),
		ImVec4(0.8f, 0.8f, 0.2f, 1.f)};
		//ImVec4(1.0f, 0.5f, 0.2f, 1.f),
		//ImVec4(0.8f, 0.6f, 1.0f, 1.f)};

	for (int l=0; l < Lnum; ++l)
	{
		PushStyleColor(ImGuiCol_Text, Lclr[l]);
		//RadioButton(Lname[l], &r);
		Checkbox(Lname[l], Lchk[l]);  x += w;
		if (l < Lnum-1)  SameLine(x);
		PopStyleColor();
	}


	//  2nd line  ----
	x = 0;  Sep(3);
	//Text(("Keys: "+i2s(keys.keys.size())).c_str());

	//  checks
	w = w1;  e = Checkbox("Pressed List", &set.bList);  x += w;  SameLine(x);
	w = w2;  e = Checkbox("Layout", &set.bLayout);  x += w;  SameLine(x);

	//  combo
	w = w3;  PushItemWidth(w);
	e = Combo("Cmb", &set.iCombo, "default\0ck3\0ck4\0\0");  //todo from keys.files[]
	if (e)  keys.LoadIndex(set.iCombo);
	PopItemWidth();  x += w + 40;  x = 475;  SameLine(x);

	//  buttons
	w = 50;  e = Button("Fit");  x += w;  SameLine(x);
	if (e && set.bLayout && xMax > 0)
	{
		//  fit window to layout  ----
		set.xwSize = min(2560, max(640, xMax + 30));  //par
		set.ywSize = yMax + h + 4;
		sf::Vector2u si(set.xwSize, set.ywSize);
		pWindow->setSize(si);
		Resize(set.xwSize, set.ywSize);
	}
	w = 100;  e = Button("Reset");  if (e)  set.fScale = 1.f;  x += w;
	w = 75;  SameLine(set.xwSize - w*2);
	e = Checkbox("vk", &set.bVK);  x += w;
	SameLine(set.xwSize - w);
	e = Checkbox("kll", &set.bKLL);  x += w;


	//  3rd line  ----
	x = 0;  Sep(1);
	w = w1;  e = Checkbox("Simple", &set.bListSimple);  x += w;  SameLine(x);

	//  scale slider
	w = w2;  Text(("Scale  "+f2s(set.fScale,2)).c_str());  x += w;  SameLine(x);
	w = set.xwSize > 720 ? 300 : 150;  //par
	PushItemWidth(w);  PushAllowKeyboardFocus(false);
	e = SliderFloat("", &set.fScale, 0.2f, 2.f, "");  PopAllowKeyboardFocus();
	if (e)  set.fScale = min(3.f, max(0.1f, set.fScale));
	PopItemWidth();  x += w + 20;  SameLine(x);

	//  fps
	w = 75;  SameLine(set.xwSize - w);
	e = Checkbox("Fps", &set.bFps);  x += w;

	//Sep(5);  Line(true);

	End();
}
