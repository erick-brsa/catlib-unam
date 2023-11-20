#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Cuenta {
    float adeudos;
    int numero_cuenta;
    int cantidad_libros;
    int libros_asociados[20];
};

struct Libro {
    char nombre[100];
    int clave;
    int cantidad;
};

int validar(struct Cuenta *usuario);

void obtenerLibros(struct Libro *libros);

void mostrarMenu();

void mostrarLibros(struct Libro *libros, int maxLibros);

void actualizarUsuarios(struct Cuenta *usuario);

void actualizarLibros(struct Libro *libros, int maxLibros, int clave);

void crearRegistro(struct Cuenta *usuario, struct Libro *libro);

void solicitarLibro(struct Cuenta *usuario, struct Libro *libros, int maxLibros);

void devolverLibro(struct Cuenta *usuario);

void pagarAdeudos();

int main() {
    struct Cuenta usuario;
    struct Libro libros[20];
    int option = 0;

    obtenerLibros(libros);

    do {
        printf("Ingrese su n%cmero de cuenta:%c", 163, 255);
        scanf("%d", &usuario.numero_cuenta);
    } while (!validar(&usuario));

    printf("Bienvenido: %d\n", usuario.numero_cuenta);

    while (option != 5) {
        mostrarMenu();
        printf("Seleccione una opci%cn:%c", 162, 255);
        scanf("%d", &option);
        switch (option) {
            case 1:
                mostrarLibros(libros, 20);
                break;
            case 2:
                solicitarLibro(&usuario, libros, 20);
                break;
            case 3:
                devolverLibro(&usuario);
                break;
            case 4:
                pagarAdeudos();
                break;
            case 5:
                printf("Bye.\n");
                break;
            default:
                printf("Seleccione una opci%cn v%clida.\n", 162, 160);
        }
    }

    return 0;
}

int validar(struct Cuenta *usuario) {
    char numero_cuenta_str[15];
    sprintf(numero_cuenta_str, "%d", usuario->numero_cuenta);

    if (strlen(numero_cuenta_str) != 9) {
        printf("El número de cuenta no es válido. Debe tener 9 dígitos.\n");
        return 0;
    }

    FILE *archivo = fopen("users.txt", "r");

    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(EXIT_FAILURE);
    }

    char linea[256];
    int cuentaEncontrada = 0;

    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        int cuentaArchivo;
        if (sscanf(linea, "%d,%f,%d", &cuentaArchivo, &usuario->adeudos, &usuario->cantidad_libros) == 3 &&
            cuentaArchivo == usuario->numero_cuenta) {
            for (int i = 0; i < usuario->cantidad_libros; i++) {
                if (sscanf(linea, "%*d,%*f,%*d,%d", &usuario->libros_asociados[i]) != 1) {
                    break;
                }
            }
            cuentaEncontrada = 1;
            break;
        }
    }

    fclose(archivo);

    if (!cuentaEncontrada) {
        printf("La cuenta con el número %d no se encontró en el archivo.\n", usuario->numero_cuenta);
    }

    return cuentaEncontrada;
}

void obtenerLibros(struct Libro *libros) {
    FILE *archivo = fopen("books.txt", "r");

    if (archivo == NULL) {
        perror("Error al abrir el archivo.\n");
        exit(EXIT_FAILURE);
    }

    while (fscanf(archivo, "%d,%d,%99[^\n]", &libros->clave, &libros->cantidad, libros->nombre) == 3) {
        libros++;
    }

    fclose(archivo);
}

void mostrarMenu() {
    printf("1. Mostrar libros.\n");
    printf("2. Solicitar Libro(s).\n");
    printf("3. Devolver Libro(s).\n");
    printf("4. Pagar adeudos.\n");
    printf("5. Salir.\n");
}

void mostrarLibros(struct Libro *libros, int maxLibros) {
    printf("Clave\t\tCantidad\t\tNombre\n");
    for (int i = 0; i < maxLibros; i++) {
        printf("%d\t\t%d\t\t%s\n", libros[i].clave, libros[i].cantidad, libros[i].nombre);
    }
}

void crearRegistro(struct Cuenta *usuario, struct Libro *libro) {
    FILE *archivo = fopen("records.txt", "a");
    if (archivo == NULL) {
        perror("Error al abrir el archivo records.txt");
        exit(EXIT_FAILURE);
    }

    // Obtener la fecha actual
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);

    // Sumar 5 días a la fecha actual
    time_t timestamp = now + 5 * 24 * 60 * 60;
    struct tm *nuevaFecha = localtime(&timestamp);

    // Formatear la fecha como dd/mm/yyyy
    char fecha[11];
    strftime(fecha, sizeof(fecha), "%d/%m/%Y", nuevaFecha);

    // Escribir en el archivo
    fprintf(archivo, "%d,%d,%s\n", usuario->numero_cuenta, libro->clave, fecha);

    fclose(archivo);
}

void actualizarUsuarios(struct Cuenta *usuario) {
    FILE *archivo = fopen("users.txt", "r"); // Abre en modo lectura

    if (archivo == NULL) {
        perror("Error al abrir el archivo users.txt para lectura.\n");
        exit(EXIT_FAILURE);
    }

    FILE *tempArchivo = fopen("temp.txt", "w"); // Abre un archivo temporal para escribir

    if (tempArchivo == NULL) {
        perror("Error al abrir el archivo temporal para escritura.\n");
        fclose(archivo);
        exit(EXIT_FAILURE);
    }

    char linea[256];
    while (fgets(linea, sizeof(linea), archivo) != NULL) {
        int cuentaArchivo;
        float adeudosArchivo;
        int cantidadLibrosArchivo;

        if (sscanf(linea, "%d,%f,%d", &cuentaArchivo, &adeudosArchivo, &cantidadLibrosArchivo) == 3 &&
            cuentaArchivo == usuario->numero_cuenta) {
            // Actualiza la cantidad de libros y agrega el nuevo código al final
            fprintf(tempArchivo, "%d,%.1f,%d", cuentaArchivo, adeudosArchivo, cantidadLibrosArchivo + 1);
            for (int i = 0; i < cantidadLibrosArchivo; i++) {
                fprintf(tempArchivo, ",%d", usuario->libros_asociados[i]);
            }
            fprintf(tempArchivo, ",%d\n", usuario->libros_asociados[cantidadLibrosArchivo]);
        } else {
            // Copia la línea sin cambios al archivo temporal
            fprintf(tempArchivo, "%s", linea);
        }
    }

    fclose(archivo);
    fclose(tempArchivo);

    remove("users.txt");        // Elimina el archivo original
    rename("temp.txt", "users.txt");  // Renombra el archivo temporal al original
}

void actualizarLibros(struct Libro *libros, int maxLibros, int clave) {
    FILE *archivo = fopen("books.txt", "r"); // Archivo original en modo lectura
    FILE *temporal = fopen("temp_books.txt", "w"); // Archivo temporal en modo escritura

    if (archivo == NULL || temporal == NULL) {
        perror("Error al abrir los archivos.\n");
        exit(EXIT_FAILURE);
    }

    int encontrado = 0;

    for (int i = 0; i < maxLibros; i++) {
        fprintf(temporal, "%d,%d,%s\n", libros[i].clave, libros[i].cantidad, libros[i].nombre);
        if (libros[i].clave == clave) {
            encontrado = 1;
        }
    }

    fclose(archivo);
    fclose(temporal);

    if (!encontrado) {
        printf("No se encontró el Libro con el código %d.\n", clave);
        remove("temp_books.txt"); // Eliminar el archivo temporal si no se encontró el Libro
        return;
    }

    remove("books.txt"); // Eliminar el archivo original
    rename("temp_books.txt", "books.txt"); // Renombrar el archivo temporal como el original
}

void solicitarLibro(struct Cuenta *usuario, struct Libro *libros, int maxLibros) {
    printf("En este momento cuentas con %d Libro(s).\n", usuario->cantidad_libros);

    if (usuario->cantidad_libros >= 20) {
        printf("Ya no puedes solicitar m%cs libros.\n", 160);
        return;
    }

    int clave;
    printf("Ingrese la clave del Libro que desea solicitar:%c", 255);
    scanf("%d", &clave);

    for (int i = 0; i < usuario->cantidad_libros; i++) {
        if (clave == usuario->libros_asociados[i]) {
            printf("Ya tienes este Libro asociado a tu Cuenta.\n");
            return;
        }
    }

    for (int i = 0; i < maxLibros; i++) {
        if (libros[i].clave == clave) {
            if (libros[i].cantidad > 0) {
                libros[i].cantidad--;
                usuario->libros_asociados[usuario->cantidad_libros] = clave;
                usuario->cantidad_libros++;
                actualizarLibros(libros, maxLibros, clave);
                actualizarUsuarios(usuario);
                crearRegistro(usuario, &libros[i]);
                printf("Libro solicitado con %cxito.\n", 130);
                printf("Tienes 5 d%cas para devolverlo.\n", 161);
                return;
            } else {
                printf("Cantidad de libros insuficientes.\n");
            }
        }
    }
    printf("No se encontr%c el libro.\n", 162);
}

void devolverLibro(struct Cuenta *usuario) {
    if (usuario->cantidad_libros == 0) {
        printf("No hay libros asociados a tu cuenta.\n");
        return;
    }

    printf("Tienes los siguientes libros:%c", 255);
    for (int i = 0; i < usuario->cantidad_libros; ++i) {
        printf("%d ", usuario->libros_asociados[i]);
    }

    int clave;
    printf("\nIngrese el c%cdigo del Libro que desea devolver:%c", 162, 255);
    scanf("%d", &clave);

    // TODO: Agregar la funcionalidad
}

void pagarAdeudos() {
    // TODO: Agregar la funcionalidad
}