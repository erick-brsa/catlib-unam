# CATLIB-UNAM

Proyecto Final de Fundamentos de Programación.

### Instrucciones
Compilar el proyecto mediante el siguiente comando:
```
gcc main.c
```
Ejecutar el proyecto:
```
./a.exe
```

### Documentación
En la parte superior del proyecto se encuentran las librerías utilizadas: `stdio.h`, `string.h`, `stdlib.h`, `time.h`. 

Después de las librerías se encuentras las definiciones de las estructuras utilizadas:
```c
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

```
Las cuentas de los usuarios tienen la estructura de Cuenta, es decir, los usuarios tienen un número de cuenta, adeudos, cantidad de libros solicitados y una lista de los libros que están asociados a su cuenta (máximo 20 libros).

Los libros tiene la estructura de Libro, es decir, tienen un nombre, una clave y la cantidad de unidades disponibles.

Después de la definición de las estructuras se encuentran las definiciones de las funciones.

`validar` se encarga de determinar si el número de cuenta ingresado tiene 9 dígitos y corrobora que este mismo número de cuenta se encuentre en el archivo `users.txt`. De ser el caso, la función llenará los datos de la variable `usuario` con la información respectiva que se encuentre en el archivo de texto.

`obtenerLibros` se encarga de leer el archivo de texto `books.txt` y llena la variable `libros`.

`mostrarMenu` despliega el menú de opciones.

`mostrarLibos` despliega una tabla con los nombres, claves y unidades de cada libro.

`actualizarUsuarios` modifica el archivo `users.txt` para agregar un libro a la lista de libros asociados.

`actualizarLibros` modifica el archivo `books.txt` para decrementar en 1 al libro que haya sido solicitado por una persona.

`crearRegistro` modifica el archivo `records.txt` para agregar una relación de un usuario con un libro y la fecha límite de devolución de ese libro.

`solicitarLibro` la función solicita el código de un libro y válida que el libro no esté asociado con la cuenta. Si la condición se cumple, entonces manda a llamar a las funciones: `actualizarUsuarios`, `actualizarLibros`, `crearRegistro`.

`devolverLibro` FALTA.

`devolverLibro` FALTA.

### Integrantes
* Bautista Rojas David
* Briones Sánchez Erick Alan
* Cruz Miranda Yasser Vladimir
* Cruz Prieto Denzel Gael
* Hernández Muciño Angel Gabriel
* Velazco Cancino Juan Antonio