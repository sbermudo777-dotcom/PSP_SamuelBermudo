package ut2_01_Hilos1;

public class HiloSumasRestas implements Runnable {

	private int numero = 1000;
	private String operacion;
	private int numveces;

	// Constructor de la clase
	public HiloSumasRestas(int numveces, String operacion) {
		super();
		this.numveces = numveces;
		this.operacion = operacion;
	}

	// Incrementará numero el numvece indicado
	public int incrementar(int numveces) {
		numero += numveces;
		return numero;
	}

	// Decrementará numero el numvece indicado
	public int decrementar(int numveces) {
		numero -= numveces;
		return numero;
	}

	public void run() {
		int resultado = numero;
		// Si la operación es “+” se invocará al método incrementar
		if ("+".equals(operacion)) {
			resultado = incrementar(numveces);
			System.out.println(Thread.currentThread().getName() + ": " + resultado);
		}
		// Si la operación es “-” se invocará al método decrementar
		if ("-".equals(operacion)) {
			resultado = decrementar(numveces);
			System.out.println(Thread.currentThread().getName() + ": " + resultado);
		}
	}

}
