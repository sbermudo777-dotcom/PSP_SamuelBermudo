package ejercicio02;

public class ConsumidorSuma extends Thread {

	/*
	 * Implementar dos consumidores: ambos hilos leerán números desde la cola. Uno
	 * de ellos calculará la suma de los números que lea, mientras que el otro
	 * calculará el producto.
	 */

	private Cola cola;
	private int sumaTotal = 0;

	public ConsumidorSuma(Cola c) {
		this.cola = c;
	}

	@Override
	public void run() {
		// El consumidor se queda esperando hasta que el productor termine
		for (int i = 0; i < 10; i++) {
			int numero = cola.consumir(1);
			sumaTotal += numero;

			try {
				Thread.sleep((int) (Math.random() * 900 + 100)); // simular consumo
			} catch (InterruptedException e) {
				Thread.currentThread().interrupt();
			}
		}

		System.out.printf("\nConsumidor TERMINADO.\nSuma total = %d", sumaTotal);
	}

}
