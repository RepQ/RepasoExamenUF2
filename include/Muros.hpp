#ifndef __MUROS_HPP__
#define __MUROS_HPP__

#define MAX_MUROS 20
#define SEPARACION_MUROS_X 700.0f
#define MIN_ALTURA_HUECO_MURO 200.0f
#define MAX_ALTURA_HUECO_MURO 300.0f

#define VELOCIDAD_MUROS_X 50.0f

#define ACELERACION_MUROS_X 5.0f

#define ANCHURA_MUROS 59
#define MIN_POSICION_MUROS_X -100.0f

#define	VELOCIDAD_MINIMA_MUROS_X 50.0f
#define	VELOCIDAD_MAXIMA_MUROS_X 750.0f
struct Muro
{
    float posX;
    int alturaSuperior;
    int alturaInferior;
    float anchura;
    
};

void IniciaMuros();

void ActualizaMuros();

int ChocaConMuro(float posX, float posY, float ancho, float alto);

float ObtenVelocidadMuros();

void RestaVelocidadMuros(float);

void DibujaMuros();


#endif
