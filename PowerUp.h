#pragma once
#include "Texture.h"

class PowerUp 
{
public:
	enum class Type 
	{  
		green = 1, 
		brown = 2	
	};
	PowerUp(const Point2f& center, PowerUp::Type type );

	void Update( float elapsedSec );
	void Draw( ) const;
	bool IsOverlapping(const Rectf& rect ) const;
	static const float radius;

private:
	Type m_Type;
	Circlef m_Shape;
	Texture m_Texture;
	Rectf m_TextClip;
	float m_Angle{ 0.0f };
	const float m_RotSpeed{ 360.0f }; // degrees per second
};


