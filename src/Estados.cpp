#include <NoEntiendo.hpp>
#include "Estados.hpp"
#include "Fondo.hpp"
#include "Demonio.hpp"
#include "Muros.hpp"
#include "Items.hpp"
#include <stdio.h>

// Estados posibles
// -1 Final
// 0  Home
// 2  Game
int estado;
int seleccionado;
float puntuacion;

void IniciaEstados()
{
    // Iniciamos el estado home
    seleccionado = 0;
	NOE_ReproduceMusica(0, 100, 100);    
    estado = 0;
    
}

void ActualizaEstado()
{
    if(estado == 0)
    {
        // Estamos en estado home
        
        if(NOE_ObtenTeclaAbajo(NOE_TECLA_A) || NOE_ObtenTeclaAbajo(NOE_TECLA_IZQUIERDA))
        {
            // Seleccionamos al boton anterior
            seleccionado = seleccionado - 1;
            if(seleccionado < 0) { seleccionado = 2; }
        }
        else if(NOE_ObtenTeclaAbajo(NOE_TECLA_D) || NOE_ObtenTeclaAbajo(NOE_TECLA_DERECHA))
        {
            // Seleccionamos al boton posterior
            seleccionado = seleccionado + 1;
            if(seleccionado > 2) { seleccionado = 0; }
        }        
        else if(NOE_ObtenTeclaAbajo(NOE_TECLA_ESPACIO))
        {
            // Comprobamos el boton seleccionado
            if(seleccionado == 0)
            {
                // Cambiamos al estado de juego iniciando
                // los modulos necesarios, la musica y la puntuacion
                IniciaFondo();
                IniciaMuros();
                IniciaDemonio();
		IniciaItems();
                NOE_ReproduceMusica(1, 100, 100);    
                puntuacion = 0;                
                estado = 2;
            }
            else if(seleccionado == 1)
            {
                // Cambiamos al estado de howto
                seleccionado = 0;
                estado = 1;
            }            
            else // seleccionado == 2
            {
                // Salimos del juego estableciendo el estado de salida
                estado = -1;
            }
            
            
        }
    }
    else if(estado == 1)
    {
        if(NOE_ObtenTeclaAbajo(NOE_TECLA_ESPACIO)) 
        {
            seleccionado = 0;
            estado = 0;
        }            
    }
    else if(estado == 2)
    {
        // Estamos en estado de juego
        
        // Obtenemos valores que necesitaremos para los calculos
        float tiempoPasado;    
        tiempoPasado = NOE_ObtenTiempoDesdeActualizacion() / 1000.0f;
        
        // Actualizamos los modulos que intervienen
        // en el juego
        ActualizaFondo();
        ActualizaMuros();
        ActualizaDemonio();
	ActualizaItems();
        
        // Actualizamos puntuacion

        puntuacion = puntuacion + ObtenVelocidadMuros() * tiempoPasado / 100.0f;
        
        if(!EstaVivoDemonio())
        {
            // Volvemos al estado home realizando
            // las acciones necesarias
            seleccionado = 0;
            NOE_ReproduceMusica(0, 100, 100);    
            estado = 0;
        }
    }
    
}

void DibujaEstado()
{
    if(estado == 0)
    {
        // Estamos en home
        
        NOE_DibujaDecorado(0);
        
        // Dibujamos botones
        int sprite;
        
        if(seleccionado == 0) { sprite = 7; }
        else { sprite = 8; }
        NOE_DibujaSprite(sprite, 302, 462, -1, -1, 0, 0);
        NOE_DibujaTexto("START GAME", 302 + 36, 462 + 20, 14, 22, 0);
        
        if(seleccionado == 1) { sprite = 7; }
        else { sprite = 8; }
        NOE_DibujaSprite(sprite, 538, 462, -1, -1, 0, 0);
        NOE_DibujaTexto("HOW TO PLAY", 538 + 36, 462 + 20, 14, 22, 0);

        if(seleccionado == 2) { sprite = 7; }
        else { sprite = 8; }
        NOE_DibujaSprite(sprite, 776, 462, -1, -1, 0, 0);
        NOE_DibujaTexto("QUIT GAME", 776 + 36, 462 + 20, 14, 22, 0);
    }
    else if(estado == 1)
    {
        NOE_DibujaDecorado(1);
        
        NOE_DibujaSprite(7, 1004, 622, -1, -1, 0, 0);
        NOE_DibujaTexto("BACK", 1004 + 36, 622 + 20, 14, 22, 0);        
    }    
    else // estado == 2
    {
        // Estamos en juego

        DibujaFondo();
        DibujaMuros();
        DibujaDemonio();
	DibujaItems();
        
        // Dibujamos el marcador
        
        NOE_DibujaSprite(12, 1031, 21, -1, -1, 0, 0);

        char textoPuntuacion[20];                
        sprintf(textoPuntuacion, "%14d", (int)puntuacion);
        
        NOE_DibujaTexto(textoPuntuacion, 1031 + 20, 21 + 10, 14, 22, 0);   
    }    
}

void	AnyadePuntuacion(int p)
{
	puntuacion += p;
}

int EsEstadoFinal()
{
    if(estado < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
