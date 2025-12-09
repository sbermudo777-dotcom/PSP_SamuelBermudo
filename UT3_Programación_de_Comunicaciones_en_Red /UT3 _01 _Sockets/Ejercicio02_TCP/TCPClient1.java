package ejercicio02tcp;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class TCPClient1 {

	public static void main(String[] args) throws IOException {

		// ---------- DATOS DEL SERVIDOR al que enviar mensaje ----------
		String host = "localhost"; // Ip del del servidor
		int puerto = 5555;

		System.out.println("PROGRAMA CLIENTE 1 INICIADO....");
		Socket Cliente1 = new Socket(host, puerto);

		// --------------- SOCKET ENVÍO ---------------

		// Creación flujo de salida hacia el servidor
		DataOutputStream flujoSalida = new DataOutputStream(Cliente1.getOutputStream());

		// Generamos 10 números aleatoriamente
		int[] arrayGenerado = new int[10];

		for (int i = 0; i < arrayGenerado.length; i++) {
			int aleatorio = (int) (Math.random() * 100 + 1); // Número aleatorio entre 1 y 100
			arrayGenerado[i] = aleatorio;
		}

		// Enviamos estos números al Servidor
		System.out.println("Enviando números...");

		for (int numero : arrayGenerado) {
			flujoSalida.writeInt(numero);
		}

		// --------------- SOCKET RECEPCIÓN ---------------

		// El socket cliente1, mostrará por pantalla los resultados obtenidos

		// Creación flujo de entrada desde el servidor
		DataInputStream flujoEntrada = new DataInputStream(Cliente1.getInputStream());

		// Recibir resultado final
		// El servidor envía un String y luego el int del resultado
		int resultadoSuma = flujoEntrada.readInt();
		int resultadoMax = flujoEntrada.readInt();
		int resultadoMin = flujoEntrada.readInt();

		System.out.println("\n--- RESULTADOS ---");
		System.out.println("La suma del array generado es: " + resultadoSuma);
		System.out.println("El número mayor del array generado es: " + resultadoMax);
		System.out.println("La número menor del array generado es: " + resultadoMin);

		// CERRAR STREAMS Y SOCKETS
		flujoEntrada.close();
		flujoSalida.close();
		Cliente1.close();

		System.out.println("\nCLIENTE 1 cerrado.");

	}

}
