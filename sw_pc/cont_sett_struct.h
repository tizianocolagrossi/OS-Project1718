/*
 * By Tiziano
 */

#pragma once
#include <xdo.h>

enum tipoElemento{mignolo, anulare, medio, indice, pollice};

typedef struct Elemento{
	int premuto;
	int statoFisico;
	char charAss;
	char *sAss;
	enum tipoElemento tipo;
}Elemento;


typedef struct Controller{
	Elemento* elementi;
	int soglia;
	int size;
	xdo_t* xdo;
	void* t_id;
}Controller;

int getSoglia(Controller* cnt);
void setSoglia(Controller* cnt, int newSgl);
void cntXdoFree(Controller* cnt);
void printControllerSetting(Controller* cnt);
void Controller_init(Controller* cnt);
void editElemCharAss(Controller* cnt, enum tipoElemento tipo, char newCharAss);
void setElemento(Controller* cnt, enum tipoElemento tipo);
void resetElemento(Controller* cnt, enum tipoElemento tipo);
void setState(Controller* cnt);
