package libproyecto;

public class Main {

    static {
        System.loadLibrary("proyecto_grafos");
    }

    public static void main(String[] argumentos) {

        grafos gr = new grafos();

        String jsonCurso = "["
                + "{\"name\": \"Matemáticas\",\"semestre\": 1,\"num_estudiantes\": 30,\"profesor\": \"Juan Pérez\",\"total_horas\": 3,\"diapreferido\": 2,\"bloquepreferido\": 4},"
                + "{\"name\": \"Cálculo\",\"semestre\": 2,\"num_estudiantes\": 35,\"profesor\": \"Ana López\",\"total_horas\": 3,\"diapreferido\": 2,\"bloquepreferido\": 4},"
                + "{\"name\": \"Algebra\",\"semestre\": 1,\"num_estudiantes\": 25,\"profesor\": \"Luis Torres\",\"total_horas\": 2,\"diapreferido\": 1,\"bloquepreferido\": 3},"
                + "{\"name\": \"Filosofía\",\"semestre\": 3,\"num_estudiantes\": 30,\"profesor\": \"Laura Martínez\",\"total_horas\": 4,\"diapreferido\": 3,\"bloquepreferido\": 5},"
                + "{\"name\": \"Música\",\"semestre\": 1,\"num_estudiantes\": 20,\"profesor\": \"Ana López\",\"total_horas\": 2,\"diapreferido\": 1,\"bloquepreferido\": 3}"
                + "]";

        String jsonSala = "["
                + "{\"nombre\": \"Sala A\",\"capacidad\": 30},"
                + "{\"nombre\": \"Sala B\",\"capacidad\": 35},"
                + "{\"nombre\": \"Sala C\",\"capacidad\": 40 }"
                + "]";

        // Llamar a la función JNI
        String asignaciones = gr.funcionAsignacion(jsonCurso, jsonSala);

        // Verificar si hay asignaciones válidas antes de imprimir
        if (!asignaciones.isEmpty()) {
            System.out.println("Asignaciones:\n" + asignaciones);
        } else {
            System.out.println("Error al realizar asignaciones.");
        }
    }
}
