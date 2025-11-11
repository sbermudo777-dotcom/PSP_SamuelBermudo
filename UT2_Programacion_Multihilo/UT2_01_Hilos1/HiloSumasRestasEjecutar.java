package ut2_01_Hilos1;

public class HiloSumasRestasEjecutar {

	public static void main(String[] args) {
		new Thread(new HiloSumasRestas(100, "+"), "HiloSuma1").start();
		new Thread(new HiloSumasRestas(100, "-"), "HiloResta2").start();
		new Thread(new HiloSumasRestas(1, "+"), "HiloSuma3").start();
		new Thread(new HiloSumasRestas(1, "-"), "HiloResta4").start();
	}

}
