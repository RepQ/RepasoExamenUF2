#include <NoEntiendo.hpp>
#include "Fondo.hpp"

ElementoFondo elementosFondo[MAX_ELEMENTOS_FONDO];

void IniciaFondo()
{
    // Obtenemos algunos valores que necesitaremos
    // para los calculos
    int anchoPantalla;
    int altoPantalla;

    anchoPantalla = NOE_ObtenAnchoPantalla();
    altoPantalla = NOE_ObtenAltoPantalla();

    // Iniciamos todos los elementos del fondo
    int i;

    i = 0;    
    
    while(i < MAX_ELEMENTOS_FONDO)
    {
        int tipo;
        
        // Los elementos pueden aparecer inicialmente en cualquier posicion
        elementosFondo[i].posX = NOE_ObtenNumeroAleatorio(MIN_POSICION_ELEMENTO_X, MAX_POSICION_ELEMENTO_X);        

        // Sorteamos el tipo de elemento
        tipo = NOE_ObtenNumeroAleatorio(0, NUM_TIPOS_ELEMENTO_FONDO - 1);
        elementosFondo[i].tipo = tipo;
        

        // Segun el tipo de elemento la posicion y tendra unos limites distintos
        if(tipo >= 0 && tipo <= 2)
        {
            elementosFondo[i].posY = NOE_ObtenNumeroAleatorio(MIN_POSICION_NUBE_Y, MAX_POSICION_NUBE_Y);        
        }
        else
        {
            elementosFondo[i].posY = NOE_ObtenNumeroAleatorio(MIN_POSICION_EDIFICIO_Y, MAX_POSICION_EDIFICIO_Y);        
        }

        i = i + 1;
    }
}

void ActualizaFondo()
{
    // Obtenemos algunos valores que vamos a necesitar
    // para los calculos

    float anchoPantalla;
    float tiempoPasado;

    tiempoPasado = NOE_ObtenTiempoDesdeActualizacion() / 1000.0f;
    anchoPantalla = NOE_ObtenAnchoPantalla();
    
        
    int i;
    
    i = 0;
    while(i < MAX_ELEMENTOS_FONDO)
    {
        // Establecemos una velocidad u otra segun el tipo de elemento
        // de que se trate.
        
        float velocidad;
        
        if(elementosFondo[i].tipo == 0) { velocidad = VELOCIDAD_NUBE_1; }
        else if(elementosFondo[i].tipo == 1) { velocidad = VELOCIDAD_NUBE_2; }
        else if(elementosFondo[i].tipo == 2) { velocidad = VELOCIDAD_NUBE_3; }
        else // elementosFondo[i].tipo == 3
        { velocidad = VELOCIDAD_EDIFICIO; }
        
        // Desplazamos el elemento hacia la izquierda a la velocidad establecida
        elementosFondo[i].posX = elementosFondo[i].posX - velocidad * tiempoPasado;
        
        if(elementosFondo[i].posX < MIN_POSICION_ELEMENTO_X)
        {
            // El elemento ha sobrepasado el limite izquierdo y tenemos que recolocarlo

            // NOTA: El codigo que sigue es muy parecido al que utilizamos para iniciar
            //       el elemento por lo que es mejor ponerlo en una funcion para evitar
            //       repetirlo
            
            int tipo;
            float minPosY;
            float maxPosY;
            
            // Movemos el elemento a una posicion x al azar, pero evitamos que aparezca
            // en pantalla dandole como minimo el valor del ancho
            elementosFondo[i].posX = NOE_ObtenNumeroAleatorio(anchoPantalla, MAX_POSICION_ELEMENTO_X);
            
            // Sorteamos un nuevo tipo
            tipo = NOE_ObtenNumeroAleatorio(0, NUM_TIPOS_ELEMENTO_FONDO - 1);
            elementosFondo[i].tipo = tipo;            
            
            // Segun el tipo de elemento la posicion y tendra unos limites distintos
            if(tipo >= 0 && tipo <= 2)
            {
                elementosFondo[i].posY = NOE_ObtenNumeroAleatorio(MIN_POSICION_NUBE_Y, MAX_POSICION_NUBE_Y);        
            }
            else
            {
                elementosFondo[i].posY = NOE_ObtenNumeroAleatorio(MIN_POSICION_EDIFICIO_Y, MAX_POSICION_EDIFICIO_Y);        
            }

        }

        i = i + 1;
    }
}

void DibujaFondo()
{   
    // Dibujamos el fondo
    
    NOE_DibujaDecorado(2);

    // Dibujamos los elementos
    
    int i;

    i = 0;
    while(i < MAX_ELEMENTOS_FONDO)
    {
        int sprite;
        
        // Segun el tipo de elemento seleccionamos un sprite u otro
        
        if(elementosFondo[i].tipo == 0) { sprite = 13; }
        else if(elementosFondo[i].tipo == 1) { sprite = 14; }
        else if(elementosFondo[i].tipo == 2) { sprite = 15; }
        else // elementosFondo[i].tipo == 3
        { sprite = 16; }
        
        // Dibujamos el sprite
        
        NOE_DibujaSprite(sprite, elementosFondo[i].posX, elementosFondo[i].posY, -1, -1, 0, 0);
        
        i = i + 1;
    }    
}