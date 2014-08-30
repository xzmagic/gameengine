#include "particles.h"
#include <list>

using namespace EngineParticles;
static std::list<Particle*> particles;

void Particle::Update(int new_time)
{
    if (time == 0)
    {
    }
    else
    {
        lives -= new_time - time;
        time = new_time;
        if (lives <= 0)
        {
            dead = true;
        }
    }
}

Particle::Particle(sprite_id _texture, int _x, int _y, int _life, int _time)
    : x(_x), y(_y), lives(_life), time(_time), texture(_texture)
{
    dead = false;
};

Particle::~Particle()
{
}

bool Particle::IsDead()
{
    return dead;
}

int Particle::GetX()
{
    return x;
}

int Particle::GetY()
{
    return y;
}

SDL_Rect* Particle::GetFrame()
{
    return NULL;
}

void Particle::Draw(Graph* g)
{

}

sprite_id Particle::GetTexture()
{
    return texture;
}

MovingParticle::MovingParticle(sprite_id _texture, int _x, int _y, int _life, int _dx, int _dy, int _time)
    : Particle(_texture, _x, _y, _life, _time), dx(_dx), dy(_dy)
{
}

void MovingParticle::Update(int new_time)
{
    x += static_cast<int>(dx * (new_time - time)/1000.0);
    y += static_cast<int>(dy * (new_time - time)/1000.0);
    Particle::Update(new_time);
}

void MovingParticle::Draw(Graph* gui)
{
    gui->DrawTexture(GetX(), GetY(), gui->GetTexture(GetTexture()), GetFrame(), 0, SDL_FLIP_NONE);
}

MovingTextParticle::MovingTextParticle(sprite_id _texture, int _x, int _y, int _life, int _dx, int _dy, int _time, size_t fontId, std::string text, SDL_Color color)
: MovingParticle(_texture, _x, _y, _life, _dx, _dy, _time)
, fontId(fontId)
, text(text)
, color(color)
{
}

void MovingTextParticle::Draw(Graph* gui)
{
    gui->WriteNormal(fontId, text, x, y, color);
}

AnimatedParticle::AnimatedParticle(sprite_id _texture,
                                   int _x,
                                   int _y,
                                   int _life,
                                   int _dx,
                                   int _dy,
                                   int _time,
                                   size_t frame_w,
                                   size_t frame_h,
                                   size_t drawn_w,
                                   size_t drawn_h,
                                   size_t frame_time,
                                   size_t frame_amount)
    : MovingParticle(_texture, _x, _y, _life, _dx, _dy, _time)
    , frameW(frame_w)
    , frameH(frame_h)
    , drawnW(drawn_w)
    , drawnH(drawn_h)
    , frameTime(frame_time)
    , prevFrameSwitch(frame_time)
    , currentFrame(0)
    , frameAmount(frame_amount)
{
}

void AnimatedParticle::Update(int new_time)
{
    if (new_time - prevFrameSwitch > frameTime)
    {
        prevFrameSwitch = new_time;
        currentFrame++;
        if (currentFrame >= frameAmount)
        {
            currentFrame = 0;
        }
    }
    MovingParticle::Update(new_time);
}

void AnimatedParticle::Draw(Graph* g)
{
    SDL_Rect frame{GetX(), GetY(), drawnW, drawnH};
    SDL_Rect framePart{ currentFrame * frameW, 0, frameW, frameH };
    g->DrawTexture(&frame, texture, &framePart, 0, SDL_FLIP_NONE);
}

void EngineParticles::Update(int time)
{
    for (std::list<Particle*>::iterator it=particles.begin(); it!=particles.end(); ++it)
    {
        (*it)->Update(time);
    }
}

void EngineParticles::Add(Particle* p)
{
    particles.push_back(p);
}

void EngineParticles::Draw(Graph* gui)
{
    std::list<Particle*>::iterator it= particles.begin();
    while (it != particles.end())
    {
        (*it)->Draw(gui);
        if ((*it)->IsDead())
        {
            delete(*it);
            it = particles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void EngineParticles::Clear()
{
    for (auto it : particles)
    {
        delete it;
    }

    particles.clear();
}