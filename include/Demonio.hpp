#ifndef __DEMONIO_HPP__
#define __DEMONIO_HPP__

#define POS_INICIAL_DEMONIO_X 100.0f
#define POS_INICIAL_DEMONIO_Y 300.0f
#define GRAVEDAD_DEMONIO_Y 2000.0f
#define IMPULSO_DEMONIO_Y 600.0f
#define SPRITE_DEMONIO 2

#define ANCHURA_DEMONIO 89
#define ALTURA_DEMONIO 150


struct Demonio
{
    float posX;
    float posY;
    float anchura;
    float altura;
    float velocidadY;
    int vivo;
    
};

void IniciaDemonio();
void ActualizaDemonio();
int EstaVivoDemonio();
void DibujaDemonio();

#endif