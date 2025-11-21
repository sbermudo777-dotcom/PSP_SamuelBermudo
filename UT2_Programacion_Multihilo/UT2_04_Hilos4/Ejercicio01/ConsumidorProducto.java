package ejercicio02;

public class ConsumidorProducto extends Thread {

	private Cola cola;
	private int productoTotal = 1;

	public ConsumidorProducto(Cola c) {
		this.cola = c;
	}

	@Override
	public void run() {
		// El consumidor se queda esperando hasta que el productor termine de producir
		for (int i = 0; i < 10; i++) {
			int numero = cola.consumir(2);
			productoTotal *= numero;

			try {
				Thread.sleep((int) (Math.random() * 900 + 100)); // simular consumo
			} catch (InterruptedException e) {
				Thread.currentThread().interrupt();
			}
		}

		System.out.printf("\nConsumidor TERMINADO.\nProducto total = %d", productoTotal);
	}

}
