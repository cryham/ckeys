#ifdef _WIN32
#include "Keyboard.h"
#include <windows.h>


HHOOK hHook = NULL;  // windows

Keys* kk = nullptr;


///  Key hook
///-----------------------------------------------------------------------------
LRESULT CALLBACK KeyHandler(int nCode, WPARAM wp, LPARAM lp)
{
	if (nCode < 0)
		return CallNextHookEx(hHook, nCode, wp, lp);

	if (nCode == HC_ACTION)
	{
		KBDLLHOOKSTRUCT kh = *((KBDLLHOOKSTRUCT*)lp);
		int vk = kh.vkCode & 0xFF,
			//sc = kh.scanCode & 0xFF,
			ext = kh.flags & LLKHF_EXTENDED > 0 ? 1 : 0;
		//if (!ext && vk > 0x2F)  vk += vk_EXTRA;

		//if (!(kh.flags & LLMHF_INJECTED))
		if (kk != nullptr)
		if (!kk->keys.empty())
		{
			int id = kk->vk2key[vk] - 1;
			if (id >= 0)
			{	if (id >= vk_EXTRA)  id -= vk_EXTRA;
				Key& k = kk->keys[id];

				if (wp == WM_SYSKEYDOWN || wp == WM_KEYDOWN)
				{
					k.on = true;  // press
				}
				else
				if (wp == WM_SYSKEYUP || wp == WM_KEYUP)
				{
					k.on = false;  // release
				}
			}
		}
		//GetKeyNameText();
	}
	return CallNextHookEx(hHook, nCode, wp, lp);
}


//  Main
///-----------------------------------------------------------------------------
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
	//  unhook
	if (hHook != NULL)
		UnhookWindowsHookEx(hHook);
}

#endif
