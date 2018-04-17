#include "stdafx.h"
#include "PowerUp.h"
#include "utils.h"
#include "Matrix2x3.h"
const float PowerUp::radius = 30.0f;

PowerUp::PowerUp(const Point2f & center, PowerUp::Type type)
	:m_Type{ type },
	m_Shape{ center,radius },
	m_Texture{ "Resources/PowerUp.png" },
	m_Angle{}
{
	if (type == PowerUp::Type(1))
	{
		m_TextClip = Rectf{ 0.0f, m_Texture.GetHeight() / 2,m_Texture.GetWidth(),m_Texture.GetHeight() / 2 }; // getting top texture
	}
	if (type == PowerUp::Type(2))
	{
		m_TextClip = Rectf{ 0.0f,0.0f,m_Texture.GetWidth(),m_Texture.GetHeight() / 2 };   // getting bottom texture
	}
}

void PowerUp::Update(float elapsedSec)
{
	m_Angle += m_RotSpeed * elapsedSec;
}

void PowerUp::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Shape.center.x, m_Shape.center.y, 0.0f);
	glRotatef(m_Angle, 0, 0, 1);
	glTranslatef(-m_Shape.center.x, -m_Shape.center.y, 0.0f);
	m_Texture.Draw(Rectf{ m_Shape.center.x - m_Shape.radius,m_Shape.center.y - m_Shape.radius,m_Shape.radius * 2,m_Shape.radius * 2 }, m_TextClip);
	glPopMatrix();
}

bool PowerUp::IsOverlapping(const Rectf & rect) const
{
	bool result{ false };
	if (utils::IsOverlapping(rect,m_Shape))
	{
		result = true;
	}
	return result;
}
