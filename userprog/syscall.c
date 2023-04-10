#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/vaddr.h"
#include "userprog/process.h"
#include "devices/shutdown.h"

static void syscall_handler(struct intr_frame *);

/*
    Lee un byte en la dirección virtual del usuario UADDR.
    UADDR debe estar por debajo de PHYS_BASE.
    Devuelve el valor del byte si tiene éxito, -1 si ocurrió una falla de segmento.
*/
static int get_user(const uint8_t *uaddr);
/*
    Lee bytes (bytes) consecutivos, tomando como base la direccion virtual del usuario
    UADDR y lo pone en dst, devuelve el numero de bytes leidos o -1 en caso exista page fault
*/
static int get_user_bytes(void *uaddr, void *dst, size_t bytes);
/*
    Termina Pintos llamando a shutdown_power_off () (declarado en devices / shutdown.h).
    Esto debería usarse pocas veces, porque pierde información sobre posibles situaciones de interbloqueo, etc.
*/
void sys_halt(void);
/*
    Termina el programa de usuario actual, devolviendo el estado al kernel. Si el padre del proceso
    lo espera (ver más abajo), este es el estado que se devolverá. Convencionalmente, un estado de 0
    indica éxito y los valores distintos de cero indican errores.
*/
void sys_exit(int);
/*
    Escribe size bytes desde el búfer al archivo abierto fd.
*/
int sys_write(int fd, const void *buffer, unsigned size);
