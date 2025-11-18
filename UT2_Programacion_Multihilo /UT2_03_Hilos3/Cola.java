package ut2_03_Hilos3;

public class Cola {

	private int clientes;

	private final int CLIENTES_MAXIMO = 5;
	private int clientesDentro = 0;

	// Constructor para manejar la cantidad de clientes que deseo
	public Cola(int clientes) {
		this.clientes = clientes;
	}

	// Método que simula la entrada al gimnasio
	public synchronized void get(int clienteId) { // Entrar
		// Mientras el gimnasio esté lleno, el cliente espera
		while (clientesDentro >= CLIENTES_MAXIMO) {
			try {
				wait(); // Espera a que alguien salga
			} catch (InterruptedException e) {
				Thread.currentThread().interrupt();
				return;
			}
		}
		// Una vez hay espacio disponible entra un nuevo cliente
		clientesDentro++;
		System.out.println("→ Cliente " + clienteId + " ENTRA al gimnasio. (Dentro: " + clientesDentro + ")");

	}

	// Método que simula la salida del gimnasio
	public synchronized void put(int clienteId) { // Salir
		System.out.println("← Cliente " + clienteId + " SALE del gimnasio. (Dentro: " + (clientesDentro - 1) + ")");
		clientesDentro--; // Reducimos menos un cliente para comprobar la función
		// Despertamos a todos los que estaban esperando (solo uno entrará)
		notifyAll();
	}

	// ---------------- Getter -----------------
	public int getClientes() {
		return clientes;
	}

}
