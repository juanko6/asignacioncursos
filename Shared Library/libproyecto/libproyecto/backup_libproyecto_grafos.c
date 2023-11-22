#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cjson/cJSON.h>
#include <jni.h>



/*
 * Class:     libproyecto_grafos
 * Method:    funcionAsignacion
 * Signature: (Ljava/lang/String;Ljava/lang/String;)I
 */


// Define el número máximo de caracteres para las cadenas de texto
#define MAXCHAR 100

int numCursos = 0;
int numSalas = 0;
int numAsignaciones = 0;

typedef char Cadena[MAXCHAR];

enum bloque {
    Bloque1,    // Bloque1(07:00 am - 09:00 am) = 0
    Bloque2,    // Bloque2(09:00 am - 11:00 am) = 1
    Bloque3,    // Bloque3(11:00 am - 01:00 am) = 2
    Bloque4,    // Bloque4(02:00 pm - 04:00 pm) = 3
    Bloque5,    // Bloque5(04:00 pm - 06:00 pm) = 4
    Bloque6,    // Bloque6(06:00 pm - 08:00 pm) = 5
    Bloque7,    // Bloque7(08:00 pm - 10:00 pm) = 6
};

enum dia {
    Lunes,    // Lunes = 0
    Martes,   // Martes = 1
    Miercoles,// Miercoles = 2
    Jueves,   // Jueves = 3
    Viernes,  // Viernes = 4
    Sabado,   // Sabado = 5
};

typedef struct {
    Cadena nombre;
    int semestre;
    int num_estudiantes;
    Cadena profesor;
    int total_horas;
    int dia;
    int bloque;
} Curso;

typedef struct {
    Cadena nombre;
    int capacidad;
} Sala;

typedef struct {
    Cadena nombre_profesor;
    Cadena nombre_sala;
    int dia_asignado;
    int bloque_asignado;
} Asignamiento;

Curso* readJsonCursos(const char *jsonString) {
    cJSON *json = cJSON_Parse(jsonString);
    if (json == NULL || !cJSON_IsArray(json)) {
        printf("Error: No se puede analizar el JSON de cursos.\n");
        cJSON_Delete(json);
        return NULL;
    }

    int arraySize = cJSON_GetArraySize(json);
    Curso *cursos = (Curso *)malloc(arraySize * sizeof(Curso));
    if (cursos == NULL) {
        printf("Error: No se puede asignar memoria para cursos.\n");
        cJSON_Delete(json);
        return NULL;
    }

    for (int i = 0; i < arraySize; i++) {
        cJSON *item = cJSON_GetArrayItem(json, i);
        cJSON *name = cJSON_GetObjectItemCaseSensitive(item, "name");
        cJSON *semestre = cJSON_GetObjectItemCaseSensitive(item, "semestre");
        cJSON *num_estudiantes = cJSON_GetObjectItemCaseSensitive(item, "num_estudiantes");
        cJSON *profesor = cJSON_GetObjectItemCaseSensitive(item, "profesor");
        cJSON *dia = cJSON_GetObjectItemCaseSensitive(item, "diapreferido");
        cJSON *bloque = cJSON_GetObjectItemCaseSensitive(item, "bloquepreferido");
        cJSON *total_horas = cJSON_GetObjectItemCaseSensitive(item, "total_horas");

        if (cJSON_IsString(name) && cJSON_IsNumber(semestre) && cJSON_IsNumber(num_estudiantes) &&
            cJSON_IsString(profesor) && cJSON_IsNumber(dia) && cJSON_IsNumber(bloque) && cJSON_IsNumber(total_horas)) {
            strcpy(cursos[i].nombre, name->valuestring);
            cursos[i].semestre = semestre->valueint;
            cursos[i].num_estudiantes = num_estudiantes->valueint;
            strcpy(cursos[i].profesor, profesor->valuestring);
            cursos[i].dia = dia->valueint;
            cursos[i].bloque = bloque->valueint;
            cursos[i].total_horas = total_horas->valueint;
            numCursos++;
        }
    }

    cJSON_Delete(json);
    return cursos;
}

Sala* readJsonSalas(const char *jsonString) {
    cJSON *json = cJSON_Parse(jsonString);
    if (json == NULL || !cJSON_IsArray(json)) {
        printf("Error: No se puede analizar el JSON de salas.\n");
        cJSON_Delete(json);
        return NULL;
    }

    int arraySize = cJSON_GetArraySize(json);
    Sala *salas = (Sala *)malloc(arraySize * sizeof(Sala));
    if (salas == NULL) {
        printf("Error: No se puede asignar memoria para salas.\n");
        cJSON_Delete(json);
        return NULL;
    }

    for (int i = 0; i < arraySize; i++) {
        cJSON *item = cJSON_GetArrayItem(json, i);
        cJSON *nombre = cJSON_GetObjectItemCaseSensitive(item, "nombre");
        cJSON *capacidad = cJSON_GetObjectItemCaseSensitive(item, "capacidad");

        if (cJSON_IsString(nombre) && cJSON_IsNumber(capacidad)) {
            strcpy(salas[i].nombre, nombre->valuestring);
            salas[i].capacidad = capacidad->valueint;
            numSalas++;
        }
    }

    cJSON_Delete(json);
    return salas;
}

char* asignarCursosASalas(Curso *cursos, Sala *salas, int numCursos, int numSalas) {
    cJSON *root = cJSON_CreateArray();

    Asignamiento *asignaciones = NULL;
    asignaciones = (Asignamiento *)malloc(sizeof(Asignamiento));
    

    for (int j = 0; j < numCursos; j++) {
        for (int i = 0; i < numSalas; i++) {
            if (salas[i].capacidad >= cursos[j].num_estudiantes) {
                bool horarioDisponible = true;

                for (int k = 0; k < numAsignaciones; k++) {
                    if (asignaciones[k].dia_asignado == cursos[j].dia &&
                        asignaciones[k].bloque_asignado == cursos[j].bloque) {
                        horarioDisponible = false;
                        break;
                    }
                }

                if (horarioDisponible) {
                    cJSON *assignment = cJSON_CreateObject();
                    cJSON_AddStringToObject(assignment, "nombre_profesor", cursos[j].profesor);
                    cJSON_AddStringToObject(assignment, "nombre_sala", salas[i].nombre);
                    cJSON_AddNumberToObject(assignment, "dia_asignado", cursos[j].dia);
                    cJSON_AddNumberToObject(assignment, "bloque_asignado", cursos[j].bloque);
                    cJSON_AddItemToArray(root, assignment);
                    numAsignaciones++;
                }
            }
        }
    }

    char *jsonString = cJSON_Print(root);
    cJSON_Delete(root);
    return jsonString;
}


JNIEXPORT jint JNICALL Java_libproyecto_grafos_funcionAsignacion
  (JNIEnv * env, jobject obj, jstring jsonCurso, jstring jsonSala) {

    // Convertir jstring a char para jsonCursos
    const char *jsonCursos = (*env)->GetStringUTFChars(env, jsonCurso, NULL);
    if (jsonCursos == NULL) {
        // Manejo de error si no se puede obtener la cadena
        return -1; // o el código de error que prefieras
    }

    // Convertir jstring a char para jsonSalas
    const char *jsonSalas = (*env)->GetStringUTFChars(env, jsonSala, NULL);
    if (jsonSalas == NULL) {
        // Manejo de error si no se puede obtener la cadena
        (*env)->ReleaseStringUTFChars(env, jsonCurso, jsonCursos);
        return -1; // o el código de error que prefieras
    }

    Curso *cursos = readJsonCursos(jsonCursos);
    Sala *salas = readJsonSalas(jsonSalas);
// aquí se debe llamar a la función que asigna los cursos a las salas

    char *asignacionesJson = asignarCursosASalas(cursos, salas, numCursos, numSalas);
    printf("\nAsignaciones:\n%s\n", asignacionesJson);

    // Liberar memoria después de usar asignacionesJson
    free(asignacionesJson);

    // Liberar memoria cuando ya no se necesite
    free(cursos);
    free(salas);

    // Liberar las cadenas obtenidas
    (*env)->ReleaseStringUTFChars(env, jsonCurso, jsonCursos);
    (*env)->ReleaseStringUTFChars(env, jsonSala, jsonSalas);

    return 0;
}
