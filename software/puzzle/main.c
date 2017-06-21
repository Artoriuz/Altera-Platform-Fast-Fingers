	#include "altera_up_avalon_parallel_port.h"			//Permite o uso das funÃ§Ãµes para escrever e ler os Parallel Port's
	#include <stdlib.h>
	#include <time.h>

	#define	NUM_0	0x01								//Valor dos segmentos, considerando display em modo cÃ¡todo comum
	#define	NUM_1	0x4F
	#define	NUM_2	0x12
	#define	NUM_3	0x06
	#define	NUM_4	0x4C
	#define	NUM_5	0x24
	#define	NUM_6	0x20
	#define	NUM_7	0x0F
	#define	NUM_8	0x00
	#define	NUM_9	0x04
	#define	NUM_A	0x08
	#define	NUM_B	0x60
	#define	NUM_C	0x31
	#define	NUM_D	0x42
	#define	NUM_E	0x30
	#define	NUM_F	0x38


	int potencia(int x, int n) {
		int aux = 1, j;
		if (n != 0) {
			for (j=1; j<=n;j++) {
				aux *= x;
			}
		}
		return aux;
	}

	int main(){
		srand(time(NULL));

		int i=0, j=0, puzzle=0, input=0, round=0, aux = 0, k=0;

		alt_up_parallel_port_dev *switcher_device;
		alt_up_parallel_port_dev *leds_device;
		alt_up_parallel_port_dev *seven_segments_device;
		alt_up_parallel_port_dev *push_buttons_device;

		switcher_device 		= alt_up_parallel_port_open_dev("/dev/switcher");
		leds_device 			= alt_up_parallel_port_open_dev("/dev/leds");
		seven_segments_device 	= alt_up_parallel_port_open_dev("/dev/seven_segments");
		push_buttons_device		= alt_up_parallel_port_open_dev("dev/push_buttons");

		while(1){
			if (round == 16){
				round = 0;
				alt_up_parallel_port_write_data(leds_device,0xff);
				k=0;
				while (k<4) {
					for (j=0; j<8; j++) {
						aux = potencia(2,j);
						alt_up_parallel_port_write_data(leds_device,aux);
						for(i=0; i<100000; i++){} //delay
					}
					for (j=7; j>=0; j--) {
						aux = potencia(2,j);
						alt_up_parallel_port_write_data(leds_device,aux);
						for(i=0; i<100000; i++){} //delay
					}
				k++;
				}
			} else {
				while (round < 16){
					switch(round){
						case 0x0:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_0); break;	//Escreve no display 7-segmentos o  valor correspondente em hexadecimal
						case 0x1:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_1); break;
						case 0x2:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_2); break;
						case 0x3:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_3); break;
						case 0x4:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_4); break;
						case 0x5:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_5); break;
						case 0x6:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_6); break;
						case 0x7:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_7); break;
						case 0x8:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_8); break;
						case 0x9:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_9); break;
						case 0xA:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_A); break;
						case 0xB:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_B); break;
						case 0xC:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_C); break;
						case 0xD:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_D); break;
						case 0xE:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_E); break;
						case 0xF:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_F); break;
						default:
							alt_up_parallel_port_write_data(seven_segments_device,NUM_0); break;
					}
					puzzle = (16+rand())%16;
					alt_up_parallel_port_write_data(leds_device,puzzle);
					for (i=0; i<1500000; i++){} //delay
					alt_up_parallel_port_write_data(leds_device,0x00);
					input = alt_up_parallel_port_read_data(switcher_device);
					if(input == puzzle){
						round++;
						for(i=0; i<500000; i++){} //delay
					} else {
						round = 0;
						alt_up_parallel_port_write_data(leds_device,0xff);
						for(i=0; i<500000; i++){} //delay
					}
				}
			}
		}
	return 0;
	}
