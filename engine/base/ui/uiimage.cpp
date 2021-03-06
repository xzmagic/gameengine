#include "uiimage.h"

UiImage::UiImage(int x,
    int y,
    size_t w,
    size_t h,
    Graph& g,
    SDL_Color borderColor,
    size_t borderWidth,
    sprite_id sprite)
    : UiObject(x, y, w, h, g, {}, borderColor, borderWidth, 0)
    , sprite(sprite)
    , showPart(false)
    , displayedArea({})
{

}

UiImage::UiImage(int x,
    int y,
    size_t w,
    size_t h,
    Graph& g,
    SDL_Color borderColor,
    SDL_Rect  displayedArea,
    size_t borderWidth,
    sprite_id sprite)
    : UiObject(x, y, w, h, g, {}, borderColor, borderWidth, 0)
    , sprite(sprite)
    , showPart(true)
    , displayedArea(displayedArea)
{

}

void UiImage::Draw()
{
    StartDraw();
    if (showPart)
    {
        if (displayedArea.w != 0)
        {
            SDL_Rect pos{ x, y, displayedArea.w, displayedArea.h };
            g->DrawTexture(&pos, sprite, &displayedArea, 0, SDL_FLIP_NONE);
        }
    }
    else
    {
        g->DrawTextureStretched((GLfloat)x, (GLfloat)y, (GLfloat)width, (GLfloat)height, g->GetTexture(sprite));
    }
    UiObject::Draw();
    EndDraw();
}

UiAnimatedImage::UiAnimatedImage(int x, int y, size_t w, size_t h, Graph& g, size_t frames, size_t frameTime, const char* fName)
    : UiImage(x, y, w, h, g, {}, 0, 0)
    , anims({ { std::string("DEFAULT"), ANIM_INFO{ 0, frames, frameTime } } })
    , img(&g, fName, DIRECTION_RIGHT, &anims, w, h, 0, "DEFAULT")
{
}

void UiAnimatedImage::Draw()
{
    StartDraw();
    img.Update(spriteTimer.GetTicks());
    img.Draw(g, x, y);
    UiObject::Draw();
    EndDraw();
}