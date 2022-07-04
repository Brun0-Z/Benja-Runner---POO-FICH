#include "Obstacle.h"

Obstacle::Obstacle() { 
	m_texture.loadFromFile("sprites/obstacle/0.png"); //se carga la textura de la trampa
	m_sprite.setPosition(850,545); //Se le asigna una posici�n inicial fuera de pantalla y sobre el piso. Podr�a usarse colisi�n con piso.
	m_sprite.setScale(3,3); //Se le asigna un tama�o
}

Vector2f Obstacle::getPosition(){
	return m_sprite.getPosition(); //Se usa para ver si el obst�culo est� fuera de pantalla
}

void Obstacle::Update(float actvelfloor){
	m_sprite.setTexture(m_texture);
		//	Se llama a la funci�n de setear texturas en cada update debido a que, de no hacerlo, la textura se pierde, y la trampa aparece como un recuadro blanco.
		//	Es un problema conocido como White Square https://en.sfml-dev.org/forums/index.php?topic=12583.0 y tiene que ver con usar vectores
		//	Se podr�a haber solucionado usando otro tipo de contenedor (como list), o cargando todas las texturas del juego desde el inicio. 
		//	Se eligi� esta soluci�n porque nos pareci� m�s intuitiva y no conlleva mayores cambios m�s que llamar al setTexture en cada update. La textura ya est� guardada y no la vuelve a abrir.
	m_sprite.move(actvelfloor,0); //Se mueve la trampa de acuerdo a la velocidad del fondo
}
