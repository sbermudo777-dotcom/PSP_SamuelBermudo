package ut2_01_Hilos1;

// --------------------- Clase CuentaBancaria ---------------------
/* Definición de la cuenta con un saldo inicial y de las operaciones para
 * ingresar dinero (método ingresarDinero) y sacar dinero (método sacarDinero) 
 * de la cuenta */
class CuentaBancaria {

	// Saldo inicial de la cuenta
	int saldo = 1000;

	int getSaldo() {
		return saldo;
	}

	void sacar(int cantidad) {
		saldo -= cantidad;
	}

	void ingresar(int cantidad) {
		saldo += cantidad;
	}

	// Método sacarDinero:
	// nombre -> persona que realiza la operación
	// importe -> cantidad a retirar
	synchronized void sacarDinero(String nombre, int importe) {
		// Después de la operación dormir el hilo
		try {
			if (getSaldo() >= importe) {
				System.out.println(nombre + " sacó de la cuenta " + importe + "€");
				Thread.sleep(1000); // dormir el hilo
				sacar(importe);
				System.out.println("Saldo actual cuenta = " + getSaldo() + "€");
			} else {
				System.out.println(nombre + " no puede sacar " + getSaldo() + " -> NO HAY SALDO SUFICIENTE");
			}
			if (getSaldo() < 0) {
				System.out.println("SALDO NEGATIVO => " + getSaldo());
			}
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}

	// Método ingresarDinero
	// nombre -> persona que realiza la operación
	// importe -> cantidad a retirar
	synchronized void ingresarDinero(String nombre, int importe) {
		// Después de la operación dormir el hilo

		try {
			System.out.println(nombre + " ingresó en la cuenta " + importe + "€");
			Thread.sleep(1000); // dormir el hilo
			ingresar(importe);
			System.out.println("Saldo actual cuenta = " + getSaldo() + "€");
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
	}
}

// --------------------- Clase HiloSacarDinero ---------------------
class HiloSacarDinero extends Thread {

	private CuentaBancaria cuenta;
	private String nombre;
	private int cantidad;

	// Constructor de la clase
	HiloSacarDinero(CuentaBancaria micuenta, String nombre, int cantidad) {
		this.cuenta = micuenta;
		this.nombre = nombre;
		this.cantidad = cantidad;
	}

	public void run() {
		cuenta.sacarDinero(nombre, cantidad);
	}
}

// --------------------- Clase HiloIngresarDinero ---------------------
class HiloIngresarDinero extends Thread {

	private CuentaBancaria cuenta;
	private String nombre;
	private int cantidad;

	// Constructor de la clase
	public HiloIngresarDinero(CuentaBancaria micuenta, String nombre, int cantidad) {
		super();
		this.cuenta = micuenta;
		this.nombre = nombre;
		this.cantidad = cantidad;
	}

	public void run() {
		cuenta.ingresarDinero(nombre, cantidad);
	}
}

// --------------------- Clase Principal ---------------------
public class HiloCajeroAutomatico {

	public static void main(String[] args) {

		CuentaBancaria c = new CuentaBancaria();

		HiloIngresarDinero Padre = new HiloIngresarDinero(c, "Padre", 200);
		HiloSacarDinero Abuelo = new HiloSacarDinero(c, "Abuelo", 600);
		HiloSacarDinero Hijo2 = new HiloSacarDinero(c, "Hijo2", 800);
		HiloSacarDinero Madre = new HiloSacarDinero(c, "Madre", 800);
		HiloIngresarDinero Hijo1 = new HiloIngresarDinero(c, "Hijo1", 300);

		Padre.start();
		Abuelo.start();
		Hijo2.start();
		Madre.start();
		Hijo1.start();

	}

}
