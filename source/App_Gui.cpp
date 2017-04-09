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
	const static int h = 84, w1 = 200, w2 = 110, w3 = 130;

	//  window
	SetNextWindowPos( ImVec2(0, set.ywSize - h),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(set.xwSize, h), ImGuiSetCond_Always);

	bool open = true;
	const int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;

	Begin("Window", &open, flags);


	//---------------------------------------------
	bool e;  // edited, changed

	Sep(5);
	//Text(("Keys: "+i2s(keys.keys.size())).c_str());
	int x = 0, w;

	//  checks
	w = w1;  e = Checkbox("Pressed List", &set.bList);  x += w;  SameLine(x);
	w = w2;  e = Checkbox("Layout", &set.bLayout);  x += w;  SameLine(x);

	//  combo
	w = w3;  PushItemWidth(w);
	e = Combo("Cmb", &set.iCombo, "default\0ck3\0ck4\0\0");  //todo from keys.files[]
	if (e)  keys.LoadIndex(set.iCombo);
	PopItemWidth();  x += w + 40;  x = 495;  SameLine(x);

	//  buttons
	w = 50;  e = Button("Fit");  x += w;  SameLine(x);
	if (e && set.bLayout && xMax > 0)
	{
		set.xwSize = min(2560, max(640, xMax + 30));  //par
		set.ywSize = yMax + h + 4;
		sf::Vector2u si(set.xwSize, set.ywSize);
		pWindow->setSize(si);
		Resize(set.xwSize, set.ywSize);
	}
	w = 100;  e = Button("Reset");  if (e)  set.fScale = 1.f;  x += w;  //SameLine(x);


	//  2nd line  ----
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
	e = Checkbox("Fps", &set.bFps);  x += w;  SameLine(x);

	//Sep(5);  Line(true);

	End();

}
