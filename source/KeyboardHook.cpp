#ifdef _WIN32
#include "Keyboard.h"
#include <algorithm>
#include <windows.h>
#include <SFML/System/Lock.hpp>


HHOOK hHook = NULL;  // windows

Keys* kk = nullptr;


///  Key hook
///-----------------------------------------------------------------------------
LRESULT CALLBACK KeyHandler(int nCode, WPARAM wp, LPARAM lp)
{
	if (nCode < 0)
		return CallNextHookEx(hHook, nCode, wp, lp);

	if (nCode == HC_ACTION && kk != nullptr)
	{
		KBDLLHOOKSTRUCT kh = *((KBDLLHOOKSTRUCT*)lp);
		int vk = kh.vkCode & 0xFF,
			sc = kh.scanCode & 0xFF,
			ext = kh.flags & LLKHF_EXTENDED > 0 ? 1 : 0;

		bool press = wp == WM_SYSKEYDOWN || wp == WM_KEYDOWN;
		bool release = wp == WM_SYSKEYUP || wp == WM_KEYUP;

		//  pressed list update
		if (press || release)
		{
			KeyCode kc;
			kc.vk = vk;  kc.sc = sc;  kc.ext = ext;

			sf::Lock(kk->mutex);
			if (press)
			{
				auto& l = kk->keyCodes;
				if (std::find(l.begin(), l.end(), kc) == l.end())
					kk->keyCodes.push_back(kc);
			}else
				kk->keyCodes.remove(kc);
		}

		//  layout update
		if (!kk->keys.empty())
		{
			int id = kk->vk2key[vk] - 1;
			if (id >= 0)
			{
				if (id >= vk_EXTRA)  id -= vk_EXTRA;
				Key& k = kk->keys[id];

				if (press)    k.on = true;
				if (release)  k.on = false;
			}
		}
	}
	return CallNextHookEx(hHook, nCode, wp, lp);
}


//  attach
void Keys::Hook()
{
	if (hHook != NULL)
		return;

	kk = this;

	//  hook kbd  * * *
	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyHandler, NULL, 0);
}

void Keys::UnHook()
{
	kk = nullptr;

	//  unhook
	if (hHook != NULL)
		UnhookWindowsHookEx(hHook);
}

#endif
