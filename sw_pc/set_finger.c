#include "set_finger.h"
#include "cont_sett_struct.h"

#include <xdo.h>
#include <stdio.h>
#include <stdlib.h>

#define DIM_VETT_MANO 4

// michele: function that controls if analog values sent by arduino
// are in a range that was set by user 
void set_finger(Controller* cnt, int soglia, int* hand){
	
	int i = DIM_VETT_MANO;
	while (i >= 0){
		if (*hand >= soglia) {
			setElemento(cnt, i);
			//printf("[set_finger]dito %d settato\n", i);
		}
		else {
			resetElemento(cnt, i);
		}
		hand++;
		i--;
	}
	setState(cnt);
}

// michele: [ALTERNATIVE]function that controls if analog values sent by arduino
// are in the calibrated range
void set_finger_calib(Controller* cnt, int* vett_soglie, int* hand){
	
	int i = DIM_VETT_MANO, c = 0;
	while (i >= 0 && c <= 4){
		if (*hand >= *vett_soglie) {
			setElemento(cnt, i);
			//printf("[set_finger]: %d set\n", i);
		}
		else {
			resetElemento(cnt, i);
		}
		hand++;        
		i--;		   
		vett_soglie++; 
		c++;	
	}
	setState(cnt);
}

