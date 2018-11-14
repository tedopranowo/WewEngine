#pragma once

#include "../Struct/Point.h"

class Renderer;

class Camera
{
private:
    Renderer* m_pRenderer;

public:
    Camera();
    ~Camera();

    void Init(Renderer* pRenderer);

    void SetPosition(const Point& position);
    const Point& GetPosition() const;
};

