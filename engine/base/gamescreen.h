/*
Author: Vladimir Slav

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef __GAMESCREEN_H__
#define __GAMESCREEN_H__

#include "graph.h"
#include "Timer.h"

class GameScreen
{
protected:
    Graph* g;
    Timer particle_timer;
    sprite_id fadeOutSprite;
    size_t fadeOutTime;
    size_t fadeOutStart;
    bool fadingOut;

    sprite_id fadeInSprite;
    size_t fadeInTime;
    size_t fadeInStart;
    bool fadingIn;

	bool keyStates[SDL_NUM_SCANCODES];
public:
    GameScreen(Graph& g);
    virtual GameScreen* Process();
    virtual void Draw();
    virtual size_t GetCurrentFont();
    virtual Graph* GetGraph();
    virtual int GetCurrentTime();
    virtual ~GameScreen() {};

    virtual void FadeIn(sprite_id fadeInSprite, size_t fadeInTime);
    virtual void OnFadeIn();
    virtual void FadeOut(sprite_id fadeOutSprite, size_t fadeOutTime);
    virtual void OnFadeOut();
};

#endif
