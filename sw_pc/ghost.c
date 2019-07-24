/*
 * SHELL SHELL SHELL SHELL SHELL SHELL SHELL SHELL SHELL SHELL SHELL
 *
 * OS-prj1819
 * 
 * shell per il progetto di sistemi operativi anno 2018/19
 * 
 */

#include "cont_sett_struct.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // per la sleep
#include <pthread.h> 


#define MAX_SIZE 50 // max caratteri in input
#define MAX_CMD 10  // max comandi per linea supportati
#define DEBUG 1

/*
 * funzione per printate di debug
 */
void debugPrint(char *msg, char *val){
	if(DEBUG) printf("\n%s %s\n", msg, val);
}
void debugPrintInt(char *msg, int val){
	if(DEBUG) printf("\n%s %d\n", msg, val);
}
void debugPrintMsg(char *msg){
	if(DEBUG) printf("\n%s\n", msg);
}


/*
 * scrive a schermo una piccola intro...
 * l'ho fatta per stare tranquillo a scrivere
 */

void init_shell(){
	printf("##########################################################################\n");
	printf("#                     SISTEMI OPERATIVI PRJ SHELL                        #\n");                                                     
	printf("##########################################################################\n");                                                     
}

/*
 * HELP per la shell
 */

void help(){
	printf(
		"\n"
		"##########################################################################\n"
		"HELP HELP HELP HELP HELP HELP HELP HELP HELP HELP HELP HELP HELP HELP HELP\n"
		"\n"
		"\nComandi riconosciuti\n\n"
		"controller: stampa lo status del cotroller ONLINE OFFLINE e i settaggi vari\n"
		"controller -m modifica i settaggi del controller\n"
		"\tcontroller -m[mignolo|anulare|medio|indice|pollice] [comando associato]\n"
		"\tESEMPIO: controller -m mignolo w\n"
		"\til mignolo trigghera il tasto s\n"
		"\n\n"
		"start avvia il controller in modo che potra essere usato su altri programmi\n"
	);
}

void sayHi(char **parsed){
	if(parsed[1]==NULL){
		printf("ERRORE: non hai passato l'argomento vedi help per la guida\n");
	} else{
		printf("Ciao %s\n", parsed[1]);
	}
}

/*
 * funzione che gestisce il thread (valori virtualizzazione etc)
 */
void *playCnt(Controller* cnt) { 
    sleep(1); 
    printf("Thread lanciato wiiiiiii \n"); 
    return NULL; 
} 

/*
 * funzione che lancia un thread per il controller
 */
void start(){
	pthread_t thread_id; 
    debugPrintMsg("Sto per lanciare il thread"); 
    pthread_create(&thread_id, NULL, playCnt, NULL); 
    pthread_join(thread_id, NULL); 
    debugPrintMsg("Thread finito\n"); 
}

/*
 * funzione per il controllo del controller
 */
void controller(char **parsed, Controller *cnt){
	if(parsed[1]==NULL){
		printControllerSetting(cnt);
		return;
	}
	if(strcmp(parsed[1],"-m")==0){
		if(parsed[2]==NULL){
			printf("devi inserire il dito di cui vuoi modificare il settaggio\n");
			return;
		}
		enum tipoElemento sw1 = -1;
		if(strcmp(parsed[2],"mignolo")==0)sw1=mignolo;
		if(strcmp(parsed[2],"anulare")==0)sw1=anulare;
		if(strcmp(parsed[2],"medio")==0)sw1=medio;
		if(strcmp(parsed[2],"indice")==0)sw1=indice;
		if(strcmp(parsed[2],"pollice")==0)sw1=pollice;
		switch (sw1){
			case 0:
				editElemCharAss(cnt, mignolo, parsed[3][0]);
				break;
			case 1:
				editElemCharAss(cnt, anulare, parsed[3][0]);
				break;
			case 2:
				editElemCharAss(cnt, medio, parsed[3][0]);
				break;
			case 3:
				editElemCharAss(cnt, indice, parsed[3][0]);
				break;
			case 4:
				editElemCharAss(cnt, pollice, parsed[3][0]);
				break;
			default:
				printf("le dita disponibili per modificare i settaggi sono:\n"
					   "\tmignolo|anulare|medio|indice|pollice\n");
				break;
		}
	}
}

/*
 * funzione per prendere comandi
 */

int getCmd(char* cmd){
	size_t characters;
	size_t bufsize = MAX_SIZE;

    printf("#> ");
// la funzione getline prende i comandi da stdin e indico la dimensione del
// buffer allocato sopra e l'indirizzo del buffer su cui scrivere    
	characters = getline(&cmd,&bufsize,stdin);
	if(characters != 0){
		//strncpy(cmd, buf, characters);
		debugPrint("FUN getCmd value >", cmd);
		return 0;
	}
	else {
		return 1;
	}
}

/*
 * funzione per lo split della tringa in input
 */
 
int splitString(char *str, char **split){
	int i;
	int len = strlen(str);
	str[len-1]='\0'; // elimino il carattere \n alla fine preso dalla getline
	debugPrint("comando preso>",str);
	for(i = 0; i < MAX_CMD; i++){
		split[i] = strsep(&str," ");
		if(split[i]==NULL) break;
		if(strlen(split[i])==0) i--;
	}
	
}

/*
 * funzione per la gestione dei comandi della shell
 */
 
int cmdHandler(char** parsed, Controller *cnt){
	
	debugPrintMsg("dentroCmdHandler");
	
	int nCmdSupportati=7, i, switchArg=100;
	char* ListCmd[nCmdSupportati];

   	ListCmd[0]="help";
   	ListCmd[1]="h";
   	ListCmd[2]="quit";
   	ListCmd[3]="exit";
   	ListCmd[4]="hi";
   	ListCmd[5]="controller";
   	ListCmd[6]="start";
   	

	debugPrintMsg("prima del for");
	debugPrint("parsed[0] in cmdHandler >", parsed[0]);
   	for(i=0; i<nCmdSupportati; i++ ){
		if(strcmp(parsed[0], ListCmd[i])==0){
			switchArg = i;
			debugPrintInt("FUN cmdHandler valore della i >", i);
			break;
		}
	}
	debugPrintMsg("dopo del for");

	switch(switchArg){
		case 0:
		case 1:
			help();
			return 1; // perche usato dall if che chiama cmdHandler!
		case 2:
		case 3:
			free(cnt->elementi);
			cntXdoFree(cnt);
			printf("ARRIVEDERCI, NON FA DANNI ME RACCOMANDO !\n");
			exit(0);
		case 4:
			sayHi(parsed);
			break;
		case 5:
			controller(parsed, cnt);
			break;
		case 6:
			start();
			break;
		default:
			printf("comando non riconosciuto, digit h o help per vedere la guida\n");
			break;
	}
}

/*
 * funzione per il parse della stringa in input
 */
 
int parseString(char *str, char** parsed, Controller *cnt){
	splitString(str, parsed);
	if (cmdHandler(parsed, cnt)) return 0;
	else return 1; 
}



int main(int argc, char **argv){
	
	char inStr[MAX_SIZE], *parsedArg[MAX_CMD];
	
	init_shell();

	Controller cnt;
	Controller_init(&cnt);
	
	while(1){
		if(getCmd(inStr)) continue;
		parseString(inStr, parsedArg, &cnt);
		
	
	}
}
