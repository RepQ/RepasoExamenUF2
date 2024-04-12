#ifndef __FONDO_HPP__
#define __FONDO_HPP__

#define MAX_ELEMENTOS_FONDO 10
#define NUM_TIPOS_ELEMENTO_FONDO 4

#define VELOCIDAD_NUBE_1 100.0f
#define VELOCIDAD_NUBE_2 60.0f
#define VELOCIDAD_NUBE_3 30.0f
#define VELOCIDAD_EDIFICIO 20.0f

#define MIN_POSICION_ELEMENTO_X -2000.0f
#define MAX_POSICION_ELEMENTO_X 2000.0f

#define MIN_POSICION_NUBE_Y 0.0f
#define MAX_POSICION_NUBE_Y 300.0f
#define MIN_POSICION_EDIFICIO_Y 500.0f
#define MAX_POSICION_EDIFICIO_Y 700.0f

struct ElementoFondo
{
    float posX;
    float posY;
    int tipo;
    
};

void IniciaFondo();

void ActualizaFondo();

void DibujaFondo();

#endif