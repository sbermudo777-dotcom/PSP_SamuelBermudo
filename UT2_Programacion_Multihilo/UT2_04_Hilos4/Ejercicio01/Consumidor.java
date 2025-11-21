package ejercicio01;

public class Consumidor extends Thread {

	/*
	 * Consumidor: lee números desde la cola y realiza una suma acumulativa de todos
	 * los números producidos.
	 */

	private Cola cola;
	private int sumaTotal = 0;

	public Consumidor(Cola c) {
		this.cola = c;
	}

	@Override
	public void run() {
		// El consumidor se queda esperando hasta que el productor termine
		for (int i = 0; i < 10; i++) {
			int numero = cola.consumir();
			sumaTotal += numero;

			try {
				Thread.sleep((int) (Math.random() * 900 + 100)); // simular consumo
			} catch (InterruptedException e) {
				Thread.currentThread().interrupt();
			}
		}

		System.out.println("Consumidor TERMINADO.\nSuma total = " + sumaTotal);
	}

}
