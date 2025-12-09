package ejercicio01tcp;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPServerSocket {

	public static void main(String[] args) throws Exception {

		int puerto = 5555;
		ServerSocket servidor = new ServerSocket(puerto);

		System.out.println("SERVIDOR TCP INICIADO en puerto: " + puerto);

		// --------------- CLIENTE 1 RECEPCIÓN ---------------
		Socket cliente1 = null;
		System.out.println("\nEsperando al CLIENTE 1...");
		cliente1 = servidor.accept();

		// Flujo de entrada del CLIENTE 1
		DataInputStream flujoEntradaCliente1 = new DataInputStream(cliente1.getInputStream());

		// El cliente 1 envía un String de saludo y un int.
		System.out.println("Mensaje de CLIENTE 1: " + flujoEntradaCliente1.readUTF());
		int numeroRecibidoCliente1 = flujoEntradaCliente1.readInt();

		// --------------- CLIENTE 2 ENVÍO ---------------
		Socket cliente2 = null;
		System.out.println("\nEsperando al CLIENTE 2...");
		cliente2 = servidor.accept();

		// Flujo de salida hacia el CLIENTE 2
		DataOutputStream flujoSalidaCliente2 = new DataOutputStream(cliente2.getOutputStream());

		// El servidor enviará el número recibido al CLIENTE 2
		flujoSalidaCliente2.writeInt(numeroRecibidoCliente1);

		// --------------- CLIENTE 2 RECEPCIÓN ---------------

		// Flujo de entrada del CLIENTE 2
		DataInputStream flujoEntradaCliente2 = new DataInputStream(cliente2.getInputStream());

		System.out.println("Recibido el resultado del CLIENTE 2...");
		int factorialRecibido = flujoEntradaCliente2.readInt(); // Almacenamos el factorial

		// Cierre de flujos y socket del Cliente 2
		flujoEntradaCliente2.close();
		flujoSalidaCliente2.close();
		cliente2.close();

		// --------------- CLIENTE 1 ENVÍO ---------------

		// Flujo de entrada del CLIENTE 2
		DataOutputStream flujoSalidaCliente1 = new DataOutputStream(cliente1.getOutputStream());

		System.out.println("\nEnviando el factorial al CLIENTE 1...");

		// El servidor enviará el número recibido al CLIENTE 1
		flujoSalidaCliente1.writeInt(factorialRecibido);

		// Cierre flujos y socket del Cliente 1
		flujoEntradaCliente1.close();
		flujoSalidaCliente1.close();
		cliente1.close();
		servidor.close();

		System.out.println("\nSERVIDOR CERRADO.");

	}

}
