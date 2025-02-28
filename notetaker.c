#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
<<<<<<< HEAD
#include <unistd.h> // Para POSIX (si fuera Linux)
#include <windows.h> // Para GetCurrentProcessId() en Windows
#include "hacking.h"

void usage(char *prog_name, char *filename) {
    printf("Usage: %s <data to add to %s>\n", prog_name, filename);
    exit(0);
}

int main(int argc, char *argv[]) {
    int userid, fd; // File descriptor
    char *buffer, *datafile;

    buffer = (char *)ec_malloc(100);
    datafile = (char *)ec_malloc(20);
<<<<<<< HEAD
    strcpy(datafile, "notes.txt"); // Usar un archivo válido en Windows

    if (argc < 2) // Si no hay argumentos en la línea de comandos, muestra la ayuda
        usage(argv[0], datafile);

    strcpy(buffer, argv[1]); // Copia el argumento en buffer

<<<<<<< HEAD
    printf("[DEBUG] buffer @ %p: '%s'\n", buffer, buffer);
    printf("[DEBUG] datafile @ %p: '%s'\n", datafile, datafile);

    // Abre el archivo
    fd = open(datafile, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
    if (fd == -1)
        fatal("in main() while opening file");

    printf("[DEBUG] file descriptor is %d\n", fd);

<<<<<<< HEAD
    // Simular un UID en Windows usando el ID del proceso
    userid = GetCurrentProcessId();

    // Escribir en el archivo
    if (write(fd, &userid, sizeof(userid)) == -1)
        fatal("in main() while writing userid to file");

    write(fd, "\n", 1);
    if (write(fd, buffer, strlen(buffer)) == -1)
        fatal("in main() while writing buffer to file");

    write(fd, "\n", 1);
    // Cierra el archivo
    if (close(fd) == -1)
        fatal("in main() while closing file");

    printf("Note has been saved.\n");

    free(buffer);
    free(datafile);

    return 0;
}
