#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    MYSQL *conn;
    int err;
    MYSQL_RES *resultado;
    MYSQL_ROW row;
    int jugador;
    int wins;

    // Creamos una conexión al servidor MySQL
    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Error al crear la conexión: %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    // Inicializamos la conexión
    conn = mysql_real_connect(conn, "localhost", "user", "pass", "juego", 0, NULL, 0);
    if (conn == NULL) {
        printf("Error al inicializar la conexión: %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    // Consulta SQL para obtener al jugador con más partidas ganadas
    err = mysql_query(conn, "SELECT Jugador, Wins FROM RankingGanadores ORDER BY Wins DESC LIMIT 1");
    if (err != 0) {
        printf("Error al consultar datos de la base %u %s\n", mysql_errno(conn), mysql_error(conn));
        exit(1);
    }

    // Recogemos el resultado de la consulta
    resultado = mysql_store_result(conn);
    row = mysql_fetch_row(resultado);
    if (row == NULL) {
        printf("No se han obtenido datos en la consulta\n");
    } else {
        // Obtenemos el jugador y el número de partidas ganadas
        jugador = atoi(row[0]);
        wins = atoi(row[1]);
        printf("El jugador con más partidas ganadas es el jugador %d, con un total de %d partidas ganadas.\n", jugador, wins);
    }

    // Cerramos la conexión con el servidor MySQL
    mysql_close(conn);
    exit(0);
}