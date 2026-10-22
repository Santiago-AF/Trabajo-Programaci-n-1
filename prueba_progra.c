#include <stdio.h>
#include <ctype.h>

#define MAX 10   

void limpiarBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

double leerMonto(void) {
    double monto;
    int valido = 0;

    do {
        printf("Ingrese el monto del cobro: ");
        if (scanf("%lf", &monto) != 1) {
            printf("Error: debe ingresar un numero.\n");
            limpiarBuffer();
        } else if (monto <= 0) {
            printf("Error: el monto debe ser mayor a cero.\n");
        } else {
            valido = 1;
        }
    } while (!valido);

    return monto;
}

char leerMedioPago(void) {
    char medio;
    int valido = 0;

    do {
        printf("Ingrese medio de pago (E: efectivo, C: credito): ");
        if (scanf(" %c", &medio) != 1) {
            printf("Error de lectura.\n");
            limpiarBuffer();
            continue;
        }
        medio = (char) toupper((unsigned char) medio);

        if (medio == 'E' || medio == 'C') {
            valido = 1;
        } else {
            printf("Error: el medio de pago debe ser 'E' o 'C'.\n");
        }
    } while (!valido);

    return medio;
}

void cargarCobros(double montos[], char medios[], int cant) {
    int i;

    for (i = 0; i < cant; i++) {
        printf("\n--- Cobro numero %d ---\n", i + 1);
        montos[i] = leerMonto();
        medios[i] = leerMedioPago();
    }
}

void listarEfectivo(double montos[], char medios[], int cant) {
    int i;
    int cantidad = 0;
    double suma = 0.0;

    printf("\n--- Listado de pagos en EFECTIVO ---\n");

    for (i = 0; i < cant; i++) {
        if (medios[i] == 'E') {
            printf("Cobro %d: $%.2f\n", i + 1, montos[i]);
            suma += montos[i];
            cantidad++;
        }
    }

    if (cantidad > 0) {
        printf("Promedio de pagos en efectivo: $%.2f\n", suma / cantidad);
    } else {
        printf("No se registraron pagos en efectivo.\n");
    }
}

void listarCredito(double montos[], char medios[], int cant) {
    int i;
    int cantidad = 0;
    double suma = 0.0;

    printf("\n--- Listado de pagos en CREDITO ---\n");

    for (i = 0; i < cant; i++) {
        if (medios[i] == 'C') {
            printf("Cobro %d: $%.2f\n", i + 1, montos[i]);
            suma += montos[i];
            cantidad++;
        }
    }

    if (cantidad > 0) {
        printf("Promedio de pagos en credito: $%.2f\n", suma / cantidad);
    } else {
        printf("No se registraron pagos en credito.\n");
    }
}

int mostrarMenu(void) {
    int opcion;
    int valido = 0;

    do {
        printf("\n===== MENU =====\n");
        printf("1) Listado de pagos en efectivo y promedio\n");
        printf("2) Listado de pagos en credito y promedio\n");
        printf("3) Fin\n");
        printf("Elija una opcion: ");

        if (scanf("%d", &opcion) != 1) {
            printf("Error: ingrese un numero valido.\n");
            limpiarBuffer();
        } else if (opcion < 1 || opcion > 3) {
            printf("Error: la opcion debe ser 1, 2 o 3.\n");
        } else {
            valido = 1;
        }
    } while (!valido);

    return opcion;
}

int main(void) {

    double montos[MAX];
    char medios[MAX];
    int opcion;

    printf("=== Carga de cobros (se ingresaran %d) ===\n", MAX);
    cargarCobros(montos, medios, MAX);

    do {
        opcion = mostrarMenu();

        switch (opcion) {
            case 1:
                listarEfectivo(montos, medios, MAX);
                break;
            case 2:
                listarCredito(montos, medios, MAX);
                break;
            case 3:
                printf("\nFin del programa.\n");
                break;
        }

    } while (opcion != 3);

    return 0;
}
