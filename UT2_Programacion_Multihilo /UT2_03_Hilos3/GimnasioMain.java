package ut2_03_Hilos3;

public class GimnasioMain {

	public static void main(String[] args) {

		Cola cola = new Cola(20); // 20 clientes

		// Creamos 20 clientes (hilos) que intentarán entrar al gimnasio
		for (int i = 1; i <= cola.getClientes(); i++) {
			Cliente cliente = new Cliente(cola, i);
			cliente.start();
		}

	}

}
