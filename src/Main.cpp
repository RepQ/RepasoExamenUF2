#include "NoEntiendo.hpp"
#include <stdio.h>
#include "Estados.hpp"

int main()
{
	NOE_Inicia();
    NOE_PonMostrarCursor(0);
    
    // Iniciamos el modulo estados
    // que sera responsable de iniciar
    // el resto de modulos si es necesario
    IniciaEstados();
	
	
    // Continuaremos mientras no se pulse escape y no se llegue al estado final
	while(!NOE_ObtenTeclaPulsada(NOE_TECLA_ESCAPE) && !EsEstadoFinal())
	{
		NOE_Actualiza();
		
        // Actualizamos el modulo estados
        // que sera responsable de actualizar
        // el resto de modulos si es necesario
        ActualizaEstado();

		NOE_LimpiaPantalla(0, 0, 0);

        // Dibujamos el modulo estados
        // que sera responsable de dibujar
        // el resto de modulos si es necesario
        DibujaEstado();
		
		NOE_MuestraPantalla();
	}

	NOE_ParaMusica();
	
	NOE_Finaliza();

    return 0;
	
}