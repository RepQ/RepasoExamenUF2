#include <NoEntiendo.hpp>
#include "Demonio.hpp"
#include "Muros.hpp"

Demonio demonio;

void IniciaDemonio()
{
    // Damos valores iniciales a todos los
    // campos de la estructura
    
    demonio.posX = POS_INICIAL_DEMONIO_X;
    demonio.posY = POS_INICIAL_DEMONIO_Y;
    demonio.velocidadY = 0;
    demonio.anchura = ANCHURA_DEMONIO;
    demonio.altura = ALTURA_DEMONIO;
    demonio.vivo = 1;
    
}

void ActualizaDemonio()
{
    // Obtenemos algunos valores que vamos a necesitar
    // para calcular el movimiento
    
    float tiempoPasado;
    int alturaPantalla;
    
    tiempoPasado = NOE_ObtenTiempoDesdeActualizacion() / 1000.0f;    
    alturaPantalla = NOE_ObtenAltoPantalla();
    
    // Procedamos el input, que afectara a la velocidad
    
    if(NOE_ObtenTeclaAbajo(NOE_TECLA_ESPACIO))
    {
        if(demonio.velocidadY >= 0)
        {
            // Con esto conseguimos que si el demonio esta cayendo
            // salga hacia arriba muy rapido, consiguiendo un efecto
            // similar al flappy bird original
            demonio.velocidadY = - IMPULSO_DEMONIO_Y;
        }
        else
        {
            // Si ya esta subiendo, anyadimos velocidad a la que lleve
            demonio.velocidadY = demonio.velocidadY - IMPULSO_DEMONIO_Y;
        }
    }
    
    // Actualizamos la posicion del demonio segun la velocidad
    
    demonio.posY = demonio.posY + demonio.velocidadY * tiempoPasado;

    // Actualizamos la velocidad segun la gravedad
    demonio.velocidadY = demonio.velocidadY + GRAVEDAD_DEMONIO_Y * tiempoPasado;

    // Detectamos las posibles colisiones

    if(demonio.posY < demonio.altura / 2)
    {
        // Hemos sobrepasado con la parte superior de la pantalla
        // devolvemos al demonio a una posicion en que este tocando
        // el borde superior sin sobrepasarlo y lo frenamos
        demonio.posY = demonio.altura / 2;
        demonio.velocidadY = 0;
    }
    else if(demonio.posY > alturaPantalla - demonio.altura / 2)
    {
        // Hemos sobrepasado la parte inferior de la pantalla
        // devolvemos al demonio a una posicion en que este tocando
        // el borde inferior sin sobrepasarlo y lo frenamos
        demonio.posY = alturaPantalla - demonio.altura / 2;
        demonio.velocidadY = 0;
    }

    // Comprobamos choques con muros
        
    if(ChocaConMuro(demonio.posX, demonio.posY, demonio.anchura, demonio.altura))
    {
        demonio.vivo = 0;
    }
    
    
}

int EstaVivoDemonio()
{
    return demonio.vivo;
}

void DibujaDemonio()
{
    // Dibujamos el sprite del demonio
    NOE_DibujaSprite(SPRITE_DEMONIO, demonio.posX - demonio.anchura / 2, demonio.posY - demonio.altura / 2, demonio.anchura, demonio.altura, 0, 0);
    
    
    int colorR;
    int colorG;
    int colorB;
    
    colorR = 0;
    colorG = 0;
    colorB = 255;
        
    
    // Dibujamos el punto central
    NOE_DibujaDisco(demonio.posX, demonio.posY, 3, colorR, colorG, colorB);

}
