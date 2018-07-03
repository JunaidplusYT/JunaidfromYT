#include "main.h" 
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"detours.lib")//lib detours versi 2
// =========================www.youtube.com/c/JunaidfromYT==================================== // 
#include <windows.h>
#include <gl/GL.h>
#include "detours.h"
#include <stdio.h>
bool wallhack = false;
bool chams = false;
bool chamscolor = false;
typedef void (WINAPI *glDrawElements_t) (GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);//function glDrawElement from opengl32
 
glDrawElements_t origglDrawElements;
 
// =============================================================================================== //
 
void WINAPI newglDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
    if (GetAsyncKeyState(VK_F1) & 1) chams = !chams;// Hotkey F11 to Active Wallhack Chams
    if (chams)
    {
        if (count >= 2500 && count <= 7000 && indices != 0 && count != 3939)
        {
            glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();
            glDepthRange(1, 0.5);
            glColorMask(0, 1, 0, 0);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            origglDrawElements(mode, count, type, indices);
            glDepthRange(0.5, 1);
            glColorMask(1, 1, 1, 1);
            glDisable(GL_BLEND);
            glPopMatrix();
            glPopAttrib();
        }
    }

    if (GetAsyncKeyState(VK_F2) & 1) chamscolor = !chamscolor;// Hotkey F12 to Change Color Chams
    if (chamscolor)
    {
        if (count >= 2500 && count <= 7000 && indices != 0 && count != 3939)// set Ultra/Exellenct Graphics
        {
            glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();
            glDepthRange(1, 0.5);
            glColorMask(1, 0, 0, 0);//Color GL (Alpha, Yellow,Pink,Blue)
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			origglDrawElements(mode, count, type, indices);
            glDepthRange(0.5, 1);
            glColorMask(1, 1, 1, 1);
            glDisable(GL_BLEND);
            glPopMatrix();// Matrix
            glPopAttrib();
        }
     
        if (count >= 2500 && count <= 7000 && indices != 0 && count != 3939)
        {
            glPushAttrib(GL_ALL_ATTRIB_BITS);
            glPushMatrix();
            glEnable(GL_BLEND);
            glBlendFunc(GL_DST_COLOR, GL_ZERO);
            glEnable(GL_LINE_SMOOTH);
            glLineWidth(2);//Line Width of body/ Shadow
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            origglDrawElements(mode, count, type, indices);
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            glDisable(GL_BLEND);
            glPopMatrix();
            glPopAttrib();
        }
    }
 
    return origglDrawElements (mode, count, type, indices);
}

// =============================================================================================== //
bool yarrakye = false;
void HookFunction()
{
    HMODULE ROSAMK = GetModuleHandle("opengl32.dll");//inject to opengl32

    if (!yarrakye)
    {
        yarrakye = true;
        if (ROSAMK)
        {
            origglDrawElements = (glDrawElements_t)(DWORD)GetProcAddress(ROSAMK, "glDrawElements");//draw chams

            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach(&(PVOID &)origglDrawElements, newglDrawElements);
            DetourTransactionCommit();
        }
    }
}

//BURADI DLLMAİN
BOOL WINAPI main(HMODULE hModule,
    DWORD dwReason,
    LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:
        HookFunction();// do  process
        MessageBox(0, "Set Graphics Game to Exellecent/Ultra \r\n[F1] Chams Color ON/OFF\r\n[F2] Choose Color Chams", "Welcome ! | JunaidfromYT ", MB_OK);
    case DLL_PROCESS_DETACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    }
    return true;
}