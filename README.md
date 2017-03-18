## Crystal Keys (cKeys)
Windows program showing pressed keys and keyboard layouts.

Made as a support program for my keyboards CK3 and CK4 (more on [my website](https://cryham.tuxfamily.org/archives/portfolio/crystal-keyboard-3-and-4)),  
to visualize layout and show bindings, also from kll (used in [controller code](https://github.com/cryham/controller)).

TODO..  
Will use SFML and ImGui for display and uses Windows Keyboard Hook to get key states.

Reads custom keyboard layouts, from json files (using jsmn parser library),  
outputed from this web based editor: www.keyboard-layout-editor.com  
Supports only basic rectangular layouts, no rotation or styling.  
The default.json layout is the ANSI 104 preset (top left combo).
