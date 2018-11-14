#pragma once

#include "../Struct/Point.h"
#include "../Struct/Rect.h"

class Window;
class Image;

class Renderer
{
protected:
    //Saves the position of the world to be rendered
    Point m_renderViewPosition;

public:
    Renderer() : m_renderViewPosition(0, 0) {}
    virtual ~Renderer() {}

	virtual bool Init() = 0;
    virtual void RenderImage(Image* pImage, const Rect& worldRectTransform) = 0;

	virtual void DrawToScreen() = 0;
	virtual void ClearScreen() = 0;

    void SetRenderPosition(const Point& viewPosition) { m_renderViewPosition = viewPosition; }
    const Point& GetRenderPosition() const { return m_renderViewPosition; }
};

