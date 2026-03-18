#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	log_info (logger,"Hola! Soy un log");
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'

	// Loggeamos el valor de config
	ip = config_get_string_value(config, "IP");
    puerto = config_get_string_value(config, "PUERTO");
    valor = config_get_string_value(config, "CLAVE");

    // Loggeamos el valor de config
    log_info(logger, "El valor de la clave leida es: %s", valor);

	/* ---------------- LEER DE CONSOLA ---------------- */

	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);
	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger;
    
    // log_create(ruta_archivo, nombre_programa, mostrar_por_consola, nivel_minimo)
    nuevo_logger = log_create("tp0.log", "CLIENTE", 1, LOG_LEVEL_INFO);

    if (nuevo_logger == NULL) {
        // Buena práctica: manejar el caso donde el logger no se pudo crear
        printf("No se pudo crear el logger\n");
        abort();
    }

    return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config;
	nuevo_config=config_create("/home/utnso/tp0/client/cliente.config");

	if (nuevo_config == NULL) {
        printf("¡No se pudo crear el config!\n");
        abort(); // Terminamos el programa si falla
    }
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
    char* leido;

    // La primera te la dejo de yapa
    leido = readline("> ");

    // El resto, las vamos leyendo y logueando hasta recibir un string vacío
    // strcmp devuelve 0 si ambos strings son exactamente iguales
    while (strcmp(leido, "") != 0) {
        
        // Logueamos lo que el usuario ingresó
        log_info(logger, "%s", leido);

        // ¡No te olvides de liberar las lineas antes de regresar!
        // Liberamos la memoria del string que acabamos de loguear
        free(leido);

        // Volvemos a leer de consola para evaluar en la siguiente vuelta del while
        leido = readline("> ");
    }

    // Al salir del while, 'leido' contiene el string vacío "". 
    // También hay que liberarlo para no perder esa memoria.
    free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete;
	t_log* logger;
	// Leemos y esta vez agregamos las lineas al paquete
	paquete=crear_paquete();
	char* leido = readline("> ");

    // El resto, las vamos leyendo y logueando hasta recibir un string vacío
    // strcmp devuelve 0 si ambos strings son exactamente iguales
    while (strcmp(leido, "") != 0) {
        
        // Logueamos lo que el usuario ingresó
        
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);

        // ¡No te olvides de liberar las lineas antes de regresar!
        // Liberamos la memoria del string que acabamos de loguear
        free(leido);

        // Volvemos a leer de consola para evaluar en la siguiente vuelta del while
        leido = readline("> ");
    }
	
	free(leido);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	enviar_paquete(paquete, conexion)
	eliminar_paquete(paquete)
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{

	if (logger != NULL) {
        log_destroy(logger);
    }
	if (config != NULL) {
        config_destroy(config);
    }
	liberar_conexion(conexion);
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
