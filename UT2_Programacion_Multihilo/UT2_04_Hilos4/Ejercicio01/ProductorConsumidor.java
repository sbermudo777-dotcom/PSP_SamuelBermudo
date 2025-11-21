package ut2_03_Hilos4;

public class ProductorConsumidor {

	public static void main(String[] args) {

		Cola cola = new Cola();

		Productor productor = new Productor(cola);
		Consumidor consumidor = new Consumidor(cola);

		productor.start();
		consumidor.start();

	}

}
