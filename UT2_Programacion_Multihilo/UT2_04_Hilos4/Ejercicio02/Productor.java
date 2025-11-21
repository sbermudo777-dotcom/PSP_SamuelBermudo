package ejercicio02;

public class Productor extends Thread {

	/*
	 * Productor: genera números enteros aleatorios y los almacena en una cola de
	 * capacidad limitada (5 elementos). Misma función que en el ejercicio anterior
	 */

	private Cola cola;

	public Productor(Cola c) {
		this.cola = c;
	}

	@Override
	public void run() {

		for (int i = 0; i < 10; i++) {
			int numero = (int) (Math.random() * 9 + 1); // genera un número aleatorio entre 1-10 para que el producto
														// no sea tan grande
			cola.producir(numero);

			try {
				Thread.sleep((int) (Math.random() * 900 + 100)); // simular tiempo de producción de forma aleatoria
			} catch (InterruptedException e) {
				Thread.currentThread().interrupt();
			}
		}

		System.out.println("Productor ha terminado de producir.");

	}

}
