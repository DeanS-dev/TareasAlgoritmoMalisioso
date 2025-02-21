#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>  // Necesario para exit()
#include <unistd.h>  // Necesario para getuid() y close()
#include "hacking.h"

#define FILENAME "/var/notes"

// Declaraciones de funciones
int print_notes(int, int, char *);
int find_user_note(int, int);
int search_note(char *, char *);
void fatal(char *);

int main(int argc, char *argv[]) {
    int userid, printing = 1, fd; // File descriptor
    char searchstring[100];

    if (argc > 1) {                     
        // Si hay un argumento, es la cadena de búsqueda
        strcpy(searchstring, argv[1]);
    } else {                             
        // De lo contrario, la dejamos vacía
        searchstring[0] = 0;          
    }

    userid = getuid();
    fd = open(FILENAME, O_RDONLY); // Abrir archivo en modo solo lectura

    if (fd == -1) {
        fatal("Error al abrir el archivo para lectura en main()");
    }

    while (printing) {
        printing = print_notes(fd, userid, searchstring);
    }

    printf("-------[ Fin de los datos de notas ]-------\n");
    close(fd);
    return 0;
}

// Función para imprimir las notas de un usuario específico que coincidan con la cadena de búsqueda
int print_notes(int fd, int uid, char *searchstring) {
    int note_length;
    char byte = 0, note_buffer[100];

    note_length = find_user_note(fd, uid);
    if (note_length == -1) {  
        return 0;  // Fin del archivo
    }

    read(fd, note_buffer, note_length); // Leer datos de la nota
    note_buffer[note_length] = 0; // Terminar la cadena correctamente

    if (search_note(note_buffer, searchstring)) { 
        printf("%s", note_buffer); // Imprimir la nota
    }

    return 1;
}

// Función para encontrar la próxima nota de un usuario dado
int find_user_note(int fd, int user_uid) {
    int note_uid = -1;
    unsigned char byte;
    int length;

    while (note_uid != user_uid) {  // Bucle hasta encontrar una nota del usuario

        if (read(fd, &note_uid, 4) != 4) {
            return -1; // Si no se leen 4 bytes, fin de archivo
        }

        if (read(fd, &byte, 1) != 1) {
            return -1;
        }

        byte = length = 0;

        while (byte != '\n') {  // Determinar la cantidad de bytes hasta el final de línea
            if (read(fd, &byte, 1) != 1) {
                return -1; // Si no se lee un byte, fin de archivo
            }
            length++;
        }
    }

    lseek(fd, length * -1, SEEK_CUR); // Retroceder la lectura del archivo
    printf("[DEBUG] Se encontró una nota de %d bytes para el usuario ID %d\n", length, note_uid);
    return length;
}

// Función para buscar una palabra clave en una nota
int search_note(char *note, char *keyword) {
    int i, keyword_length, match = 0;
    keyword_length = strlen(keyword);

    if (keyword_length == 0) {
        return 1; // Si no hay cadena de búsqueda, siempre hay coincidencia
    }

    for (i = 0; i < strlen(note); i++) { // Iterar sobre la nota
        if (note[i] == keyword[match]) {  
            match++; // Coincidencia encontrada, continuar verificando
        } else {       
            if (note[i] == keyword[0]) { 
                match = 1; // Reiniciar coincidencia si coincide con el primer caracter
            } else {
                match = 0; // Reiniciar coincidencia
            }
        }
        if (match == keyword_length) {
            return 1; // Se encontró coincidencia completa
        }
    }

    return 0; // No hay coincidencia
}

