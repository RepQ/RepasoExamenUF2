#include <NoEntiendo.hpp>
#include <math.h>
#include "Muros.hpp"

Muro muros[MAX_MUROS];

float velocidadMuros;

// Funcion privada que nos da la posicion x del
// muro mas alejado
float ObtenMaxPosicionMuroX()
{
    int j;
    float maxPosicionMuroX;
    
    maxPosicionMuroX = 0;
                
    j = 0;
    
    while(j < MAX_MUROS)
    {
        if(muros[j].posX > maxPosicionMuroX)
        {
            maxPosicionMuroX = muros[j].posX;
        }
        
        j = j + 1;
    }
    
    return maxPosicionMuroX;
    
}

// Funcion privada que inicia el muro que le indiquemos
// tiene dos modos de funcionamiento segun lo que valga
// el segundo parametro, o bien pone el muro en la 
// posicion que tiene al inicio del juego o bien lo
// coloca tras el ultimo
void IniciaMuro(int i, int esInicioJuego)
{
    // Obtenemos valores que necesitaremos para los calculos
    int anchuraPantalla;
    int alturaPantalla;
    
    anchuraPantalla = NOE_ObtenAnchoPantalla();
    alturaPantalla = NOE_ObtenAltoPantalla();
    
    if(esInicioJuego)
    {
        // Calculamos una posicion x inicial para el muro que lo
        // separe del anterior y que evite que aparezca en pantalla
        muros[i].posX = anchuraPantalla + i * SEPARACION_MUROS_X;
        
    }
    else
    {
        // Calculamos la posicion x del muro mas alejado
            
        float maxPosicionMuroX;
        maxPosicionMuroX = ObtenMaxPosicionMuroX();
            
        // Colocamos el muro a continuacion del mas alejado
        muros[i].posX = maxPosicionMuroX + SEPARACION_MUROS_X;        
    }
    
    // Calculamos una altura de hueco aleatoria
    float alturaHueco;        
    alturaHueco = NOE_ObtenNumeroAleatorio(MIN_ALTURA_HUECO_MURO, MAX_ALTURA_HUECO_MURO);
    
    // Calculamos la altura del muro superior, que tambien puede ser aleatoria
    // pero dejando espacio suficiente para el hueco
    float alturaSuperior = NOE_ObtenNumeroAleatorio(0, alturaPantalla - alturaHueco);
    
    muros[i].alturaSuperior = alturaSuperior;
    
    // El muro inferior tendra la altura que quede despues de quitar las alturas del hueco
    // y del muro superior
    muros[i].alturaInferior = alturaPantalla - alturaHueco - alturaSuperior;
    
    muros[i].anchura = ANCHURA_MUROS;        
    
}


void IniciaMuros()
{
    // Obtenemos valores que necesitaremos para los calculos
    
    int i;

    i = 0;    
    
    while(i < MAX_MUROS)
    {
        IniciaMuro(i, 1);        
        i = i + 1;
    }
    
    velocidadMuros = VELOCIDAD_MUROS_X;
}

void ActualizaMuros()
{
  

    // Obtenermos valores que necesitaremos para los calculos    
    float tiempoPasado;
    
    tiempoPasado = NOE_ObtenTiempoDesdeActualizacion() / 1000.0f;
    
    
    int i;

    i = 0;
    
    while(i < MAX_MUROS)
    {
        // Movemos el muro hacia la izquierda
        muros[i].posX = muros[i].posX - tiempoPasado * velocidadMuros;
        
        if(muros[i].posX < MIN_POSICION_MUROS_X)
        {
            // Este muro sobrepasa el limite izquierdo
            
            IniciaMuro(i, 0);
            
        }
	//Se añade restriccion para la velocidad maxima de los muros
	if (velocidadMuros <= 750)
		velocidadMuros += (5.0f * tiempoPasado); // Se añade progesion lineal de la velocidad de los muros
        
        i = i + 1;
    }
}

int ChocaConMuro(float posX, float posY, float anchura, float altura)
{
    // Obtenemos valores que necesitaremos para los calculos
    
    int alturaPantalla;
        
    alturaPantalla = NOE_ObtenAltoPantalla();

    int i;
    int choca;
    
    i = 0;
    choca = 0;
    
    while(i < MAX_MUROS && !choca)
    {
        // Comprobaremos si el centro del demonio esta dentro del muro superior o del inferior
        if(posX >= muros[i].posX && posX <= muros[i].posX + muros[i].anchura &&
           (posY >= alturaPantalla - muros[i].alturaInferior || posY <= muros[i].alturaSuperior))
        {
            choca = 1;
        }
        else
        {
            i = i + 1;
        }
    }
    
    return choca;
}


float ObtenVelocidadMuros()
{
    return velocidadMuros;
}

void DibujaMuros()
{
    // Obtenemos valores que necesitaremos para los calculos
    
    int alturaPantalla;

    alturaPantalla = NOE_ObtenAltoPantalla();

    int i;
    
    i = 0;

    while(i < MAX_MUROS)
    {
        NOE_DibujaSprite(9, muros[i].posX, 0, ANCHURA_MUROS, muros[i].alturaSuperior, 0, 0);
        NOE_DibujaSprite(9, muros[i].posX, alturaPantalla - muros[i].alturaInferior, ANCHURA_MUROS, muros[i].alturaInferior, 0, 0);
        
        NOE_DibujaCaja(muros[i].posX, 0, ANCHURA_MUROS, muros[i].alturaSuperior, 0, 0, 255);
        NOE_DibujaCaja(muros[i].posX, alturaPantalla - muros[i].alturaInferior, ANCHURA_MUROS, muros[i].alturaInferior, 0, 0, 255);
        
        i = i + 1;
    }
}
