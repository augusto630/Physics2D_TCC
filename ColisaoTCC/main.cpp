#include "main.h"

int main(void)
{
	
	Scene *cena = new Scene();

	cena->setDrawFPS(true);
	cena->setMaxFPS(60);
	cena->Init();
	//TODO DESENHAR FUNDO

	cena->Start();

	cena->Stop();

	delete cena;

	return 0;

	/*if(Init() == -1){Destr(); return -1;};

	GameLoop();
	
	Destr();
	return 0;*/



}