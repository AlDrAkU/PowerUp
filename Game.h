#pragma once
#include "PowerUp.h"
class Game
{
public:
	explicit Game( const Window& window );
	Game( const Game& other ) = delete;
	Game& operator=( const Game& other ) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( );

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	Window m_Window;
	Point2f m_MousePos{};
	static const int m_NrPowerUps{ 10 };
	PowerUp* m_pPowerUps[m_NrPowerUps]{};
	int m_ActNrPowerUps{};

	Point2f m_PowerUpsCenters[m_NrPowerUps]{};
	PowerUp::Type m_PowerUpTypes[m_NrPowerUps]{};
	bool m_PowerUpsDestroyed[m_NrPowerUps]{};
	Rectf m_Destroyer{0.0f,0.0f,20.0f,20.0f};

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( );

	void ShowTestMessage( ) const;
	void ShowNrPowerUps( ) const;
	void CreatePowerUps( );
	void UpdatePowerUps( float elapsedSec );
	void DrawPowerUps( ) const;
	void DeletePowerUps( );

	void MoveDestroyer( const Point2f& newCenter );
	void DrawDestroyer( );
	void VerifyOverlapping( );
};


