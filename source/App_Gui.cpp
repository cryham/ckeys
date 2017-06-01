#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include "App.h"
#include "Util.h"
using namespace std;  using namespace ImGui;  using namespace SFML;


//  Gui draw and process
///-----------------------------------------------------------------------------
void App::Gui()
{
	//  window
	SetNextWindowPos( ImVec2(set.xRWndSize, set.ywSize - set.yGuiSize), ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(set.xGuiSize-set.xRWndSize, set.yGuiSize), ImGuiSetCond_Always);
	const static int w1 = set.xGui1, w2 = set.xGui2, w3 = set.xGui3;

	bool open = true;
	const int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;
	Begin("Window", &open, flags);


	bool e;  // edited, changed
	int x = 0, w;

	//  1st line
	//---------------------------------------------
	Sep(1);
	w = w2;  Text("Layers");  x += w;  SameLine(x);
	w = 60;
	const int Lnum = 3;
	bool* Lchk[Lnum] = {&set.bL1, &set.bL2, &set.bL3};
	const char* Lname[Lnum] = {"L1", "L2", "L3"};
	const ImVec4 Lclr[Lnum] = {
		ImVec4(0.3f, 0.6f, 1.0f, 1.f),
		ImVec4(0.4f, 0.85f, 0.2f, 1.f),
		ImVec4(0.8f, 0.8f, 0.2f, 1.f)};

	for (int l=0; l < Lnum; ++l)
	{
		PushStyleColor(ImGuiCol_Text, Lclr[l]);
		Checkbox(Lname[l], Lchk[l]);  x += w;
		if (l < Lnum-1)  SameLine(x);
		PopStyleColor();
	}

	//  2nd line
	//---------------------------------------------
	x = 0;  Sep(3);
	//Text(("Keys: "+i2s(keys.keys.size())).c_str());
	w = w2;  Text("Layout");  x += w;  SameLine(x);

	//  combo
	w = w3;  PushItemWidth(w);
	e = Combo("Cmb", &set.iCombo, "default\0ck3\0ck4\0\0");  //todo from keys.files[]
	if (e)  keys.LoadIndex(set.iCombo, set.logOut);
	PopItemWidth();  x += w + 40;  x = 315;  SameLine(x);

	//  buttons
	w = 50;  e = Button("Fit");  x += w;  SameLine(x);
	if (e && set.bLayout && xMax > 0)
	{
		//  fit window to layout  ----
		set.xwSize = min(2560, max(640, xMax + 30));  //par
		set.ywSize = yMax + set.yGuiSize + 4;
		sf::Vector2u si(set.xwSize, set.ywSize);
		pWindow->setSize(si);
		Resize(set.xwSize, set.ywSize);
	}
	w = 100;  e = Button("Reset");  if (e)  set.fScale = 1.f;  x += w;


	//  3rd line
	//---------------------------------------------
	x = 0;  Sep(1);

	//  scale slider
	w = w2;  Text(("Scale  "+f2s(set.fScale,2)).c_str());  x += w;  SameLine(x);
	w = set.xwSize > 720 ? 320 : 150;  //par
	PushItemWidth(w);  PushAllowKeyboardFocus(false);
	e = SliderFloat("", &set.fScale, 0.2f, 2.f, "");  PopAllowKeyboardFocus();
	if (e)  set.fScale = min(3.f, max(0.1f, set.fScale));
	PopItemWidth();  x += w + 20;  SameLine(x);

	End();


	//  left window, menu tabs
	//---------------------------------------------
	int h = set.ywSize - set.yGuiSize;
	SetNextWindowPos( ImVec2(0, h), ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(set.xRWndSize, h), ImGuiSetCond_Always);
	Begin("WndDbg", &open, flags);

	Sep(1);
	e = Button("Options");  if (e)  options = !options;
	Sep(1);
	e = Button("Graphics");  if (e)  graphics = !graphics;
	Sep(1);
	e = Button("Help");  //if (e)  graphics = !graphics;

	End();


	//  Graphics window
	//---------------------------------------------
	const int xt = 120,
		xts = 90, xs = 100, ws = xs+30;

	if (graphics)
	{
		SetNextWindowPos( ImVec2(set.xRWndSize, set.ywSize - set.yGuiSize), ImGuiSetCond_Always);
		SetNextWindowSize(ImVec2(set.xwSize - set.xRWndSize, set.yGuiSize), ImGuiSetCond_Always);
		Begin("GraphicsWnd", &open, flags);

		Sep(1);
		x = 0;  w = xt;  Text("Font: ");  x += w;  SameLine(x);
		PushItemWidth(xs);
		e = SliderInt("Font", &set.iFontH, 4, 30);  x += ws;  SameLine(x);
		Text("Gui");  x += xts/2;  SameLine(x);
		e = SliderInt("Gui", &set.iFontGui, 4, 30);  x += ws;  SameLine(x);
		PopItemWidth();
		e = Checkbox("Bold", &set.bBold);  x += w;  //SameLine(x);

		Sep(3);
		x = 0;  w = xt;  Text("Graphics: ");  x += w;  SameLine(x);
		w = xt;  e = Checkbox("Vsync", &set.vsync);  x += w;  SameLine(x);
		PushItemWidth(xs);
		Text("Limit Fps");  x += xts;  SameLine(x);
		e = SliderInt("lim", &set.limitFps, 0, 200);  x += ws;  SameLine(x);
		Text("Sleep");  x += xts;  SameLine(x);
		e = SliderInt("sl", &set.iSleep, 0, 30);  x += ws;  SameLine(x);
		Text("Aliasing");  x += xts;  SameLine(x);
		e = SliderInt("al", &set.iAliasing, 0, 16);  x += ws;  //SameLine(x);
		PopItemWidth();

		End();
	}

	//  Options window
	//---------------------------------------------
	if (options)
	{
		SetNextWindowPos( ImVec2(set.xRWndSize, set.ywSize - set.yGuiSize), ImGuiSetCond_Always);
		SetNextWindowSize(ImVec2(set.xwSize - set.xRWndSize, set.yGuiSize), ImGuiSetCond_Always);
		Begin("OptionsWnd", &open, flags);

		Sep(1);
		x = 0;  w = xt;  //Text(": ");  x += w;  SameLine(x);
		w = w1;  e = Checkbox("Pressed List", &set.bList);  x += w;  SameLine(x);
		w = w2;  e = Checkbox("Simple", &set.bListSimple);  x += w;  SameLine(x);
		w = w2;  e = Checkbox("Layout", &set.bLayout);  x += w;  //SameLine(x);

		Sep(3);
		x = 0;  w = xt;  Text("Test: ");  x += w;  SameLine(x);
		w = 90;
		e = Checkbox("VK", &set.bVK);  x += w;  SameLine(x);
		e = Checkbox("KLL", &set.bKLL);  x += w;  SameLine(x);
		e = Checkbox("Fps", &set.bFps);  x += w;  //SameLine(x);

		Sep(1);
		x = 0;  w = xt;  Text("Program: ");  x += w;  SameLine(x);
		w = 120;
		e = Checkbox("Esc Quits", &set.escQuit);  x += w;  SameLine(x);
		e = Checkbox("Log Output", &set.logOut);  x += w;  SameLine(x);

		End();
	}
}
