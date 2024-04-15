#include "NoEntiendo.hpp"
#include "Items.hpp"
#include "Muros.hpp"
#include "Estados.hpp"

Item	items[MAX_ITEMS];

float	ObtenMaxPosicionItem()
{
	int	j;
	float	maxPosicionItemX;

	maxPosicionItemX = 0;
	j = 0;

	while (j < MAX_ITEMS)
	{
		if (items[j].posX > maxPosicionItemX)
			maxPosicionItemX = items[j].posX;
		j++;
	}

	return (maxPosicionItemX);
}

void	IniciaItem(int i, int esInicioJuego)
{
	float	tiempoPasado = NOE_ObtenTiempoDesdeActualizacion();
	float	wScreen = NOE_ObtenAnchoPantalla();
	float	hScreen = NOE_ObtenAltoPantalla();
	float	randPosX;
	float	randPosY;
	int	randTipo = NOE_ObtenNumeroAleatorio(0, 3);

	if (esInicioJuego)
	{
		items[i].ancho = 100;
		items[i].alto = 100;

		randPosX = NOE_ObtenNumeroAleatorio(ANCHURA_MUROS, SEPARACION_MUROS_X);
		randPosY = NOE_ObtenNumeroAleatorio(items[i].alto, hScreen - items[i].alto);

		items[i].posX = wScreen + randPosX + i * SEPARACION_ITEMS_X;
		items[i].posY = randPosY;
		switch(randTipo)
		{
			case 0:
				items[i].tipo = PUNTOS_BAJO;
				break ;
			case 1:
				items[i].tipo = PUNTOS_MEDIO;
				break ;
			case 2:
				items[i].tipo = PUNTOS_ALTO;
				break ;
			case 3:
				items[i].tipo = FRENAR;
				break ;
		}
	}
	else
	{
		float maxPosX;
		maxPosX = ObtenMaxPosicionItem();
		items[i].posX = maxPosX + SEPARACION_ITEMS_X;
	}
}

void	IniciaItems()
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		IniciaItem(i, 1);
	}
}

void	ActualizaItems()
{
	float	velocidadMurosX;
	float	tiempoPasado;

	velocidadMurosX = ObtenVelocidadMuros();
	tiempoPasado = NOE_ObtenTiempoDesdeActualizacion() / 1000.0f;
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		items[i].posX -= velocidadMurosX * tiempoPasado;
		if (items[i].posX < -1 *items[i].ancho)
			IniciaItem(i, 0);
	}
}

int	ChocaConItem(int i, float posX, float posY)
{
	float	radiusX;
	float	radiusY;
	float	radius;

	float	distX;
	float	distY;


	radius = items[i].ancho / 2;
	radiusX = items[i].posX + (items[i].ancho / 2);
	radiusY = items[i].posY + (items[i].alto / 2);

	distX = (posX - radiusX) * (posX - radiusX);
	distY = (posY - radiusY) * (posY - radiusY);

	if (distX + distY < radius * radius)
		return (1);
	else
		return (0);
}

int	ObtenNumItems()
{
	float	numItems;

	numItems = 0;
	for (int i = 0; i < MAX_ITEMS; i++)
		numItems++;
	return (numItems);
}

void	ConsumeItem(int i)
{
	float maxPosItem;

	maxPosItem = ObtenMaxPosicionItem();
	switch(items[i].tipo)
	{
		case PUNTOS_BAJO:
			AnyadePuntuacion(100);
			break ;
		case PUNTOS_MEDIO:
			AnyadePuntuacion(300);
			break ;
		case PUNTOS_ALTO:
			AnyadePuntuacion(500);
			break ;
		case FRENAR:
			RestaVelocidadMuros(200);
	}
	IniciaItem(i, 1);
}

void	DibujaItems()
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		switch(items[i].tipo)
		{
			case PUNTOS_BAJO:
				NOE_DibujaSprite(17, items[i].posX, items[i].posY, -1, -1, 0, 0);
				break ;
			case PUNTOS_MEDIO:
				NOE_DibujaSprite(18, items[i].posX, items[i].posY, -1, -1, 0, 0);
				break ;
			case PUNTOS_ALTO:
				NOE_DibujaSprite(19, items[i].posX, items[i].posY, -1, -1, 0, 0);
				break ;
			case FRENAR:
				NOE_DibujaSprite(20, items[i].posX, items[i].posY, -1, -1, 0, 0);
				break ;
		}
	}
}
