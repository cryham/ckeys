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
	SetNextWindowPos( ImVec2(0, 40),  ImGuiSetCond_Always);
	SetNextWindowSize(ImVec2(400, 300), ImGuiSetCond_Always);

	bool open = true;
	const int flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize;

	Begin("Window", &open, flags);


	//  Pattern  Properties
	//---------------------------------------------
	Text("Properties");

	bool e;  // edited, changed


	//  editbox
	static char ed[100]={0};

	PushItemWidth(140);
	e = InputText("Edit", ed, sizeof(ed));
	PopItemWidth();
	Sep(5);

	//  sliders
	static int i = 0;
	e = SliderInt("SldInt", &i, 0, 255, "");  SameLine();  Text(("i"+i2s(i)).c_str());

	static float f = 0.f;
	e = SliderFloat("SldFlt", &f, 0.f, 1.f, "");  SameLine();  Text(("f"+f2s(f,3)).c_str());

	//  check
	static bool b = false;
	Sep(5);  Line(true);
	e = Checkbox("Check", &b);

	//  button
	Sep(5);
	e = Button("Save");  //if (e)  Save();

	//  combobox
	static int c = 0;
	Sep(5);
	e = Combo("Cmb", &c, "aaa\0bbb\0\0");
	//Line();

	End();
}
