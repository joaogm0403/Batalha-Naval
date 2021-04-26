// Os arquivos de cabeçalho
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>

// Atributos da tela
#define LARGURA_TELA 874
#define ALTURA_TELA 620

void error_msg(char *text){
	al_show_native_message_box(NULL,"ERRO",
		"Ocorreu um erro e o programa sera finalizado",
		text,NULL,ALLEGRO_MESSAGEBOX_ERROR);
}

int main(void){

    const int FPS = 60;
    int menu;
    int jogar;
    int regras;
    int sobre;
    bool done = false;


	ALLEGRO_DISPLAY *display = NULL;


	ALLEGRO_BITMAP *menu_jogar = NULL;
	ALLEGRO_BITMAP *menu_regras = NULL;
	ALLEGRO_BITMAP *menu_sobre = NULL;

	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

   //Inicialização da biblioteca Allegro
	if (!al_init()){
		error_msg("Falha ao inicializar a Allegro");
		return -1;
	}

	//tenta iniciar o módulo de imagens
	if (!al_init_image_addon()){
		error_msg("Falha ao inicializar add-on allegro_image");
		return -1;
	}

	//cria display em janela
	display = al_create_display(LARGURA_TELA, ALTURA_TELA);
	//caso al_create_display retorne NULL, encerra programa
	if (!display){
		error_msg("Falha ao criar janela");
		return -1;
	}

	//carrega imagem
	menu_jogar = al_load_bitmap("menu_jogar.png");
	//caso al_load_bitmap retorne NULL, encerra programa
	if (!menu_jogar){
		error_msg("Falha ao carregar o arquivo de imagem");
		al_destroy_display(display);
		return -1;
	}

	//cria fila de eventos
	fila_eventos = al_create_event_queue();
	//caso al_create_event_queue retorne NULL, destroi a janela e encerra o programa
	if (!fila_eventos){
		error_msg("Falha ao criar fila de eventos");
		al_destroy_display(display);
		return -1;
	}

	//registra eventos da janela em fila_eventos
	al_register_event_source(fila_eventos, al_get_display_event_source(display));

	//desenha imagem no display ativo em X:0 Y:0
	al_draw_bitmap(menu_jogar, 0, 0, 0);

	//atualiza tela
	al_flip_display();


	while(!done){

		//declara vriavel que recebe o evento
		ALLEGRO_EVENT evento;

		//espero por um evento da fila, e guarda em evento
		al_wait_for_event(fila_eventos, &evento);

        //Sair do jogo quando a tecla ESC for pressionada
		if(evento.type == ALLEGRO_EVENT_KEY_DOWN){
            if(evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                done = true;
            }
		}

		//Sair do jogo quando pressionar o X da janela
		if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}


		al_flip_display();
	}

	//destroi janela e fila de eventos ao fim
	al_destroy_display(display);
	al_destroy_event_queue(fila_eventos);

	return 0;
}
