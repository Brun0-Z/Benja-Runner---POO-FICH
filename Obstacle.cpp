#include "Obstacle.h"

Obstacle::Obstacle() { 
	m_texture.loadFromFile("sprites/obstacle/0.png"); //se carga la textura de la trampa
	m_sprite.setPosition(850,545); //Se le asigna una posición inicial fuera de pantalla y sobre el piso. Podría usarse colisión con piso.
	m_sprite.setScale(3,3); //Se le asigna un tamaño
}

Vector2f Obstacle::getPosition(){
	return m_sprite.getPosition(); //Se usa para ver si el obstáculo está fuera de pantalla
}

void Obstacle::Update(float actvelfloor){
	m_sprite.setTexture(m_texture);
		//	Se llama a la función de setear texturas en cada update debido a que, de no hacerlo, la textura se pierde, y la trampa aparece como un recuadro blanco.
		//	Es un problema conocido como White Square https://en.sfml-dev.org/forums/index.php?topic=12583.0 y tiene que ver con usar vectores
		//	Se podría haber solucionado usando otro tipo de contenedor (como list), o cargando todas las texturas del juego desde el inicio. 
		//	Se eligió esta solución porque nos pareció más intuitiva y no conlleva mayores cambios más que llamar al setTexture en cada update. La textura ya está guardada y no la vuelve a abrir.
	m_sprite.move(actvelfloor,0); //Se mueve la trampa de acuerdo a la velocidad del fondo
}
