#include "../libs/imgui.h"
#include "../libs/imgui-SFML.h"
#include "App.h"
#include "Util.h"
using namespace ImGui;  using namespace SFML;


//  Gui draw and process
///-----------------------------------------------------------------------------
void App::Gui()
{

	//  window
	SetNextWindowPos( ImVec2(0, set.ywSize-60),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(set.xwSize, 60), ImGuiSetCond_Always);

	bool open = true;
	const int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;

	Begin("Window", &open, flags);


	//---------------------------------------------
	bool e;  // edited, changed

	Sep(5);
	//Text(("Keys: "+i2s(keys.keys.size())).c_str());
	int x = 0, w;

	//  checks
	w = 180;  e = Checkbox("Pressed List", &set.bList);  x += w;  SameLine(x);
	w = 100;  e = Checkbox("Layout", &set.bLayout);  x += w;  SameLine(x);

	//  combo
	w = 140;  PushItemWidth(w);
	e = Combo("Cmb", &set.iCombo, "default\0ck3\0ck4\0\0");  //todo from keys.files[]
	if (e)  keys.LoadIndex(set.iCombo);
	PopItemWidth();  x += w + 40;  SameLine(x);


	//  slider
	w = 90;  Text(("Scale "+f2s(set.fScale,2)).c_str());  x += w;  SameLine(x);
	w = 150;  PushItemWidth(w);  PushAllowKeyboardFocus(false);
	e = SliderFloat("SldFlt", &set.fScale, 0.2f, 2.f, "");  PopAllowKeyboardFocus();
	PopItemWidth();  x += w + 20;  SameLine(x);

	//  button
	w = 90;  e = Button("Reset");  if (e)  set.fScale = 1.f;  x += w;  SameLine(x);

	//  fps
	w = 60;  e = Checkbox("Fps", &set.bFps);  x += w;  SameLine(x);

	//Sep(5);  Line(true);

	End();

}
