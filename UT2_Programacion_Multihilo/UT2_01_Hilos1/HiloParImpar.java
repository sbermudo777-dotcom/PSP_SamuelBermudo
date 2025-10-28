package ejercicios;

public class HiloParImpar implements Runnable {

	private int tipo;

	public HiloParImpar(int tipo) {
		super();
		this.tipo = tipo;
	}

	public void run() {
		if (tipo == 1) { // Tipo 1
			for (int i = 1; i <= 100; i++) {
				if (i % 2 == 0)
					System.out.println(" HILO " + tipo + " generando número par " + i);
			}
		}
		if (tipo == 2) { // Tipo 2
			for (int i = 101; i <= 200; i++) {
				if (i % 2 != 0)
					System.out.println(" HILO " + tipo + " generando número impar " + i);
			}
		}
	}

	public static void main(String[] args) throws InterruptedException {

		Thread t1 = new Thread(new HiloParImpar(1));
		Thread t2 = new Thread(new HiloParImpar(2));

		// Modificar el programa para que muestre siempre los impares en primer lugar
		t2.start(); // Inicia t2 impares
		t2.join(); // Sigue hasta terminar

		t1.start(); // Inicia t1 pares
		t1.join(); // Sigue hasta teminar

		System.out.println("Fin del programa."); // Fin

	}

}
