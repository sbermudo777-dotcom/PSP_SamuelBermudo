package ejercicio02;

import java.util.LinkedList;

public class Cola {

	private LinkedList<Integer> cantidad = new LinkedList<>();
	private final int MAXIMO = 5; // Máximo 5 elementos producidos en la cola

	/*
	 * Implementar sincronización en los métodos de cada clase para asegurar que no
	 * haya problemas de acceso concurrente.
	 */

	// Sincronización del productor
	public synchronized void producir(int numero) { // Put
		while (cantidad.size() == MAXIMO) { // si la cola está llena, espera.
			try {
				wait();
			} catch (InterruptedException e) {
				Thread.currentThread().interrupt();
			}
		}

		cantidad.add(numero);
		System.out.println("Productor produce: " + numero + " → Cola: " + cantidad.size() + "/5");

		notifyAll(); // avisar a los consumidores que hay algún producto
	}

	// Sincronización del consumidor
	public synchronized int consumir(int clienteId) { // Get
		while (cantidad.isEmpty()) { // si la cola está vacía espera al productor
			try {
				wait();
			} catch (InterruptedException e) {
				Thread.currentThread().interrupt();
			}
		}

		int numero = cantidad.removeFirst();
		System.out
				.println("    Consumidor " + clienteId + " consume: " + numero + " → Cola: " + cantidad.size() + "/5");

		notifyAll(); // avisar al productor que hay espacio en la cola
		return numero;
	}

}
