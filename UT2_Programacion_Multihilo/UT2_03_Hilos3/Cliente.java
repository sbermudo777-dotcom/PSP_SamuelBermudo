package ut2_03_Hilos3;

public class Cliente extends Thread {

	private Cola cola;
	private int id;

	// El constructor recibe la cola y un id para el hilo Cliente
	public Cliente(Cola c, int id) {
		cola = c;
		this.id = id;
	}

	public void run() {
		cola.get(id);
		// Mensaje de entrada
		try {
			sleep(1000); // Simula el tiempo entrenando
		} catch (InterruptedException e) {
			Thread.currentThread().interrupt();
		}

		// Mensaje de salida
		cola.put(id);
	}

}