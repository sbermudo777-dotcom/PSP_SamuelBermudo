package ejercicio02tcp;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Arrays;

public class TCPServer {

	public static void main(String[] args) throws IOException {

		// --------------- ASOCIACIÓN DEL SOCKET AL PUERTO ---------------
		int puerto = 5555;
		ServerSocket servidor = new ServerSocket(puerto);

		System.out.println("SERVIDOR TCP INICIADO en puerto: " + puerto);

		while (true) { // El socket servidor funciona de manera indefinida
			// --------------- CLIENTE 1 RECEPCIÓN ---------------
			Socket cliente1 = null;
			System.out.println("\nEsperando al CLIENTE 1...");
			cliente1 = servidor.accept();

			// Flujo de entrada del CLIENTE 1
			DataInputStream flujoEntradaCliente1 = new DataInputStream(cliente1.getInputStream());

			// Crear array y leer cada número
			int[] numerosRecibidos = new int[10];

			for (int i = 0; i < numerosRecibidos.length; i++) {
				numerosRecibidos[i] = flujoEntradaCliente1.readInt();
			}

			// Mostramos los números recibidos
			System.out.println("Array recibido: " + Arrays.toString(numerosRecibidos));

			// Suma de los elementos del array
			int suma = 0;
			int min = 0;
			int max = 0;

			for (int i = 0; i < numerosRecibidos.length; i++) {
				suma += numerosRecibidos[i];
			}

			// Número mayor y menor
			for (int i = 0; i < numerosRecibidos.length; i++) {

				if (i == 0) {
					max = numerosRecibidos[0];
					min = numerosRecibidos[0];
				}

				if (numerosRecibidos[i] > max) {
					max = numerosRecibidos[i];
				}
				if (numerosRecibidos[i] < min) {
					min = numerosRecibidos[i];
				}

			}

			// --------------- CLIENTE 1 ENVÍO ---------------
			DataOutputStream flujoSalidaCliente1 = new DataOutputStream(cliente1.getOutputStream());

			System.out.println("\nEnviando los resultados al CLIENTE 1...");

			// El servidor enviará la suma al CLIENTE 1
			flujoSalidaCliente1.writeInt(suma);
			flujoSalidaCliente1.writeInt(max);
			flujoSalidaCliente1.writeInt(min);
		}

		// Cierre flujos y socket del Cliente 1
		// flujoEntradaCliente1.close();
		// flujoSalidaCliente1.close();
		// cliente1.close();
		// servidor.close();

	}

}
