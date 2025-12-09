package ejercicio01tcp;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class TCPClientSocket1 {

	public static void main(String[] args) throws Exception {

		Scanner sc = new Scanner(System.in);

		/*
		 * El socket cliente1, solicitará por pantalla al usuario un número y se lo
		 * enviará al servidor
		 */

		String host = "localhost"; // Ip del del servidor
		int puerto = 5555;

		System.out.println("PROGRAMA CLIENTE 1 INICIADO....");
		Socket Cliente1 = new Socket(host, puerto);

		// --------------- SOCKET ENVÍO ---------------

		// Creación flujo de salida hacia el servidor
		DataOutputStream flujoSalida = new DataOutputStream(Cliente1.getOutputStream());

		System.out.print("Introduce un número: ");
		int numero = sc.nextInt();

		// Enviando datos al Socket
		System.out.println("Número " + numero + " enviado al SERVIDOR.");
		flujoSalida.writeUTF("Enviado el número " + numero + " desde el CLIENTE 1"); // Duda
		flujoSalida.writeInt(numero);

		// --------------- SOCKET RECEPCIÓN ---------------

		// El socket cliente1, mostrará por pantalla el resultado obtenido

		// Creación flujo de entrada desde el servidor
		DataInputStream flujoEntrada = new DataInputStream(Cliente1.getInputStream());

		// Recibir resultado final
		// El servidor envía un String y luego el int del resultado
		int resultadoFinal = flujoEntrada.readInt();

		System.out.println("\n--- RESULTADO FINAL ---");
		System.out.println("El factorial es: " + resultadoFinal);

		// CERRAR STREAMS Y SOCKETS
		flujoEntrada.close();
		flujoSalida.close();
		Cliente1.close();
		sc.close();

		System.out.println("\nCLIENTE 1 cerrado.");

	}

}
