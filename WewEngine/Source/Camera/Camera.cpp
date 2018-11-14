#include "Camera.h"

#include "../Renderer/Renderer.h"

Camera::Camera()
    : m_pRenderer(nullptr)
{
}


Camera::~Camera()
{
}

void Camera::Init(Renderer * pRenderer)
{
    m_pRenderer = pRenderer;
}

void Camera::SetPosition(const Point & position)
{
    m_pRenderer->SetRenderPosition(position);
}

const Point& Camera::GetPosition() const
{
    return m_pRenderer->GetRenderPosition();
}
