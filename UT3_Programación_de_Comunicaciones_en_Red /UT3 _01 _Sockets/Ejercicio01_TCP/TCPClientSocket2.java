package ejercicio01tcp;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;

public class TCPClientSocket2 {

	public static void main(String[] args) throws Exception {

		// El cliente2, calculará el factorial y devolverá el resultado al servidor

		String host = "localhost"; // Ip del del servidor
		int puerto = 5555;

		System.out.println("PROGRAMA CLIENTE 2 INICIADO....\n");
		Socket Cliente2 = new Socket(host, puerto);

		// --------------- SOCKET RECEPCIÓN ---------------

		// Creación del flujo de entrada desde el servidor
		DataInputStream flujoEntrada = new DataInputStream(Cliente2.getInputStream());

		int numeroRecibidoSocket = flujoEntrada.readInt();

		// Calculando el factorial del número.
		int factorial = valorFactorial(numeroRecibidoSocket);

		// --------------- SOCKET ENVÍO ---------------

		// Creación flujo de salida hacia el servidor
		DataOutputStream flujoSalida = new DataOutputStream(Cliente2.getOutputStream());

		System.out.println("Enviando valor factorial al SERVIDOR.");
		flujoSalida.writeInt(factorial);

		// CERRAR STREAMS Y SOCKETS
		flujoEntrada.close();
		flujoSalida.close();
		Cliente2.close();

		System.out.println("\nCLIENTE 2 cerrado.");

	}

	// Método para calcular el factorial
	public static int valorFactorial(int numero) {
		if (numero < 0) {
			return 0;
		}

		int factorial = 1;
		while (numero > 0) {
			factorial *= numero;
			numero--;
		}
		return factorial;
	}

}
