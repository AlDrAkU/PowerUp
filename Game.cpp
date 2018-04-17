#include "stdafx.h"
#include "Game.h"
#include "utils.h"

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	CreatePowerUps( );
	ShowTestMessage( );
}


void Game::Cleanup( )
{
	DeletePowerUps( );
}

void Game::Update( float elapsedSec )
{
	UpdatePowerUps( elapsedSec );
	MoveDestroyer( m_MousePos);
	VerifyOverlapping( );
}

void Game::Draw( )
{
	ClearBackground( );
	DrawPowerUps( );
	DrawDestroyer( );
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	m_MousePos.x = float( e.x );
	m_MousePos.y = m_Window.height - e.y;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
}

void Game::ClearBackground( )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
void Game::ShowTestMessage( ) const
{
	std::cout << "PowerUp test :\n";
	std::cout << "1. Verify that the colored circles coincide with the drawn PowerUp objects.\n";
	std::cout << "2. Verify that a PowerUp object disappears when the mouse's red rectangle overlaps it.\n";
	std::cout << "3. Verify that the number of drawn PowerUp objects is equal to the displayed number.\n" ;
	ShowNrPowerUps( );
}
void Game::ShowNrPowerUps( ) const
{
	std::cout << "Number of PowerUp objects " << m_ActNrPowerUps << "\n";
}

void Game::CreatePowerUps( )
{
	// Create 10 PowerUp objects at random positions 
	float radius = PowerUp::radius;
	int min{ int( radius ) };
	int maxX{ int( m_Window.width - radius  ) };
	int maxY{ int( m_Window.height - radius  ) };

	for ( int idx{ 0 }; idx < m_NrPowerUps; ++idx )
	{
		Point2f center{float(rand()%( maxX - min + 1) + min), float( rand( ) % ( maxY - min + 1 ) + min ) };
		PowerUp::Type type = ( idx % 2 == 0 ) ? PowerUp::Type::green : PowerUp::Type::brown;
		m_PowerUpsCenters[idx] = center;
		m_PowerUpTypes[idx] = type;
		m_PowerUpsDestroyed[idx] = false;
		m_pPowerUps[idx] = new PowerUp( center, type );
		++m_ActNrPowerUps;
	}
}

void Game::DeletePowerUps( )
{
	for ( int idx{ 0 }; idx < m_NrPowerUps; ++idx )
	{
		delete m_pPowerUps[idx];
		m_pPowerUps[idx] = nullptr;
	}
}
void Game::DrawPowerUps( ) const
{
	for ( int idx{ 0 }; idx < m_NrPowerUps; ++idx )
	{
		if ( m_pPowerUps[idx] != nullptr )
		{
			m_pPowerUps[idx]->Draw( );
			if ( m_PowerUpTypes[idx] == PowerUp::Type::brown )
			{
				utils::SetColor( { 1.0f,0.5f,0.2f,0.5f } );
			}
			else
			{
				utils::SetColor( { 0.5f,1.0f,0.5f,0.5f } );
			}
			utils::FillEllipse( m_PowerUpsCenters[idx], PowerUp::radius, PowerUp::radius);
		}
	}
}

void Game::UpdatePowerUps( float elapsedSec )
{
	for ( int idx{ 0 }; idx < m_NrPowerUps; ++idx )
	{
		if ( m_pPowerUps[idx] != nullptr)
		{
			m_pPowerUps[idx]->Update( elapsedSec);
		}
	}
}

void Game::MoveDestroyer(const Point2f& newCenter )
{
	m_Destroyer.left = newCenter.x - m_Destroyer.width / 2;
	m_Destroyer.bottom = newCenter.y - m_Destroyer.height / 2;
}

void Game::VerifyOverlapping( )
{
	bool powerUpDeleted{ false };
	for ( int idx{ 0 }; idx < m_NrPowerUps; ++idx )
	{
		if ( m_pPowerUps[idx] != nullptr && m_pPowerUps[idx]->IsOverlapping( m_Destroyer ) )
		{
			delete m_pPowerUps[idx];
			m_pPowerUps[idx] = nullptr;
			--m_ActNrPowerUps;
			powerUpDeleted = true;
		}
	}
	if ( powerUpDeleted )
	{
		ShowNrPowerUps( );
	}
}
void Game::DrawDestroyer( )
{
	utils::SetColor( { 1.0f,0.0f,0.0f,1.0f } );
	utils::FillRect( m_Destroyer );
}
