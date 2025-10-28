package ejercicios;

public class HiloParImpar implements Runnable {

	public void run() {
		if (Thread.currentThread().getName() == "Tipo1") { // Tipo 1
			for (int i = 1; i <= 100; i++) {
				if (i % 2 == 0)
					System.out.println(" HILO 2 generando número par " + i);
			}
		}
		if (Thread.currentThread().getName() == "Tipo2") { // Tipo 2
			for (int i = 101; i <= 200; i++) {
				if (i % 2 != 0)
					System.out.println(" HILO 2 generando número impar " + i);
			}
		}
	}

	public static void main(String[] args) {

		new Thread(new HiloParImpar(), "Tipo1").start();
		new Thread(new HiloParImpar(), "Tipo2").start();

		// Modificar el programa para que muestre siempre los impares en primer lugar

	}

}
