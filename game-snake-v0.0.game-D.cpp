
/* 
*************************************************************************************************

C++ 5.11 V. 0.0.0
Test game and github test, it's not optimized or anything, it's trash. But if you want, you can see it.

***************************************************************************************************
*/
#include<windows.h> 
#include<iostream>
#include<conio.h> 
#include<stdlib.h> 
/* CONSTANTES */
#define ARRIBA 72
#define IZQUIERDA 75
#define DERECHA 77
#define ABAJO 80
#define ESC 27
/* VARIABLES */
int cuerpo[200][2];
int n = 1; 
int tam = 7;
int x = 10, y = 12;
int dir = 3;
int xc = 30, yc = 15;
int velocidad = 100, h = 1;
int score = 0;
char tecla;

/* FUNCION GOTOXY*/
void gotoxy(int x, int y) 
{
	HANDLE hCon;
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}
/* FUNCION LIMITES JUEGO*/
void pintar() {
	// LINEAS HORIZONTALES ARRIBA Y ABAJO (205)
	for (int i = 2; i < 78; i++) {
		gotoxy(i, 3); printf("%c", 205); //Ar
		gotoxy(i, 23); printf("%c", 205); //Ab
	}
	// LINEAS VERTICALES IZ Y DER (186)
	for (int i = 4; i < 23; i++) {
		gotoxy(2, i); printf("%c", 186); //IZ
		gotoxy(77, i); printf("%c", 186); //DE
	}
	// LINEAS DE LAS ESQUINAS 
	gotoxy(2, 3); printf("%c", 201);
	gotoxy(2, 23); printf("%c", 200);
	gotoxy(77, 3); printf("%c", 187);
	gotoxy(77, 23); printf("%c", 188);
}

void guardar_posicion() {

	cuerpo[n][0] = x;
	cuerpo[n][1] = y;
	n++;

	if (n == tam) n = 1; // Que n no sobrepase el tamano 

}
// FUNCION DIBUJAR CUERPO
void dibujar_cuerpo() {
	for (int i = 1; i < tam; i++) {
		gotoxy(cuerpo[i][0], cuerpo[i][1]);
		printf("*");
	}
}
// FUNCION DIBUJAR CUERPO
void borrar_cuerpo() {
	/*
	for(int i = 1;i<tam;i++){
		gotoxy(cuerpo[i][0], cuerpo[i][1]);
		printf(" ");
	}
	*/
	gotoxy(cuerpo[n][0], cuerpo[n][1]); printf(" ");
}
// FUNCION TECLAS
void teclear() {
	//if (kbhit()) { DEPRECATED 
	if (_kbhit()) {
		// tecla = getch(); DEPRECATED

		tecla = _getch();

		switch (tecla) {
		case ARRIBA:
			if (dir != 2)
				dir = 1;
			break;
		case ABAJO:
			if (dir != 1)
				dir = 2;
			break;
		case DERECHA:
			if (dir != 4)
				dir = 3;
			break;
		case IZQUIERDA:
			if (dir != 3)
				dir = 4;
			break;
		}
	}
}

// FUNCION CAMBIAR VELOCIDAD
void cambiar_velocidad() {
	if (score == h * 20) {
		velocidad -= 10;
		h++;
	}
}
// FUNCION COMIDA
void comida() {
	if (x == xc && y == yc) {
		xc = (rand() % 73) + 4; // (0-72)
		yc = (rand() % 19) + 4; // (0
		tam++;
		score += 10; // de 10 en 10
		gotoxy(xc, yc); printf("%c", 4);
		cambiar_velocidad();
	}

}
// FUNCION GAMEOVER(choque de "paredes")
bool game_over() {
	/*
	if(y == 3 || y == 23 || x == 2 || x == 77) return true; // margen de arriba, abajo,izquierdo,derecho
	return false;
	*/
	if (y == 3 || y == 23 || x == 2 || x == 77) return false; // margen de arriba, abajo,izquierdo,derecho

	for (int j = tam - 1; j > 0; j--) {
		if (cuerpo[j][0] == x && cuerpo[j][1] == y)
			return false;
	}
	return true;

}
// FUNCION PUNTOS
void puntos() {
	gotoxy(3, 1); printf("score %d", score);
}

int main() {

	/*
	// Posiciones al azar(3)
	for(int j = 0;j < 3 ; j++){

		for(int i = 0; j < 2; i++){

			cuerpo[j][i] = rand()%10;

		}

	}
	// Imprimo las posiciones
	for(int j = 0;j < 3 ; j++){

		gotoxy(cuerpo[j][0],cuerpo[j][1]);

		printf("*");

	}
	*/

	/* CUERPO DE LA SERPIENTE
	// Posiciones
	cuerpo[0][0] = 3;
	cuerpo[0][1] = 5;
	cuerpo[1][0] = 4;
	cuerpo[1][1] = 5;
	cuerpo[2][0] = 5;
	cuerpo[2][1] = 5;

	// ver las posiciones
	for(int j = 0;j < 3 ; j++){
		gotoxy(cuerpo[j][0],cuerpo[j][1]);
		printf("*");

	}
	*/
	pintar();
	gotoxy(xc, yc); printf("%c", 4); // LA PRIMERA COMIDA
	
	/* JUEGO */
	//while(tecla != ESC && !game_over()){
	while (tecla != ESC && game_over()) {
		// FUNCION QUE BORRA EL CUERPO DE LA SERPIENTE
		borrar_cuerpo();
		// FUNCION QUE GUARDA LA POSICION DE LA SERPIENTE
		guardar_posicion();
		// FUNCION QUE DIBUJA EL CUERPO DE LA SERPIENTE
		dibujar_cuerpo();
		// x++;
		comida();
		puntos();
		// cambiar_velocidad();
		teclear();
		teclear();
		// casos (coordenadas invertidas)
		if (dir == 1)y--;
		if (dir == 2)y++;
		if (dir == 3)x++;
		if (dir == 4)x--;
		// Sleep(80);
		Sleep(velocidad);
	}
	//pintar();
	system("pause>null");
	return 0;
}
