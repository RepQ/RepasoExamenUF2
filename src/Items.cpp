#include "NoEntiendo.hpp"
#include "Items.hpp"
#include "Muros.hpp"

Item	items[MAX_ITEMS];

void	IniciaItem(int i, int esInicioJuego)
{
	float	tiempoPasado = NOE_ObtenTiempoDesdeActualizacion();
	float wScreen = NOE_ObtenAnchoPantalla();
	float hScreen = NOE_ObtenAltoPantalla();
	float 	randPosX = NOE_ObtenNumeroAleatorio(wScreen / 2, wScreen - items[i].ancho);
	float 	randPosY = NOE_ObtenNumeroAleatorio(items[i].alto, hScreen - items[i].alto);
	int	randTipo = NOE_ObtenNumeroAleatorio(0, 3);

	if (esInicioJuego)
	{
		items[i].posX = randPosX;
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
		items[i].posX += (ObtenVelocidadMuros() * tiempoPasado);
	}
}

void	ActualizaItems()
{
}
