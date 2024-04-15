#ifndef __ITEMS_HPP__
#define __ITEMS_HPP__

#define MAX_ITEMS 10
#define	SEPARACION_ITEMS_X 1400

enum TipoItem
{
    PUNTOS_BAJO,
    PUNTOS_MEDIO,
    PUNTOS_ALTO,
    FRENAR
};

struct Item
{
    float posX;
    float posY;
    float ancho;
    float alto;
    TipoItem tipo;
};

void IniciaItems();

void ActualizaItems();

int ChocaConItem(int i, float posX, float posY);

int ObtenNumItems();

void ConsumeItem(int i);

void DibujaItems();





#endif
