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
	SetNextWindowPos( ImVec2(0, 5),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(set.xwSize, 60), ImGuiSetCond_Always);

	bool open = true;
	const int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;

	Begin("Window", &open, flags);


	//---------------------------------------------
	bool e;  // edited, changed

	//  combobox
	Sep(5);
	//Text(("Keys: "+i2s(keys.keys.size())).c_str());

	int x = 0, w;
	w = 100;  Text("Layout: ");  x += w;  SameLine(x);
	w = 140;  PushItemWidth(w);
	e = Combo("Cmb", &set.iCombo, "default\0ck3\0ck4\0\0");  //todo from keys.files
	if (e)  keys.LoadIndex(set.iCombo);
	PopItemWidth();  x += w + 40;  SameLine(x);

	//  sliders
	static float f = 1.f;
	w = 160;  PushItemWidth(w);
	e = SliderFloat("SldFlt", &f, 0.5f, 2.f, "");
	PopItemWidth();  x += w + 20;  SameLine(x);
	w = 120;  Text(("Scale "+f2s(f,2)).c_str());  x += w;

	//  check
	static bool b = false;
	SameLine(x);
	w = 120;  e = Checkbox("Check", &b);  x += w;

	//  button
	SameLine(x);
	e = Button("Save");  //if (e)  Save();

	//Sep(5);  Line(true);

	End();

}
