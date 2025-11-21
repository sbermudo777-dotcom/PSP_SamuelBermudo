package ejercicio02;

public class ProductorConsumidor {

	public static void main(String[] args) {

		Cola cola = new Cola();

		Productor productor = new Productor(cola);
		ConsumidorSuma consumidor1 = new ConsumidorSuma(cola);
		ConsumidorProducto consumidor2 = new ConsumidorProducto(cola);

		productor.start();
		consumidor1.start();
		consumidor2.start();

	}

}
