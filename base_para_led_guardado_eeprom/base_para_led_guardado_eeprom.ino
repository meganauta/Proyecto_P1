#include <IRremote.h>  //librerias para el IR



//Encendido y apagado de el led de 7 segmentos
bool n[11][7]={ {1,1,1,1,1,1,0},
             {0,1,1,0,0,0,0},
             {1,1,0,1,1,0,1},
             {1,1,1,1,0,0,1},
             {0,1,1,0,0,1,1},
             {1,0,1,1,0,1,1},
             {1,0,1,1,1,1,1},
             {1,1,1,0,0,0,0},
             {1,1,1,1,1,1,1},
             {1,1,1,0,0,1,1},
             {0,0,0,0,0,0,0} };


//pines que se usan
int definir_pines_led_display[]={33,34,35,36,37,38,39}; //pin a = 33 ping b = 34... ping g =39
int definir_pusadores[]={27,28,29,30};
int definir_led_aviso[]={31,32};
int bucle;
int numero_inicio=0;

//configuracon global
void setup() {
  // put your setup code here, to run once:
  for(bucle=0; bucle<=sizeof(definir_pines_led_display)/sizeof(definir_pines_led_display[0]);bucle++){
    pinMode(definir_pines_led_display[bucle], OUTPUT);
  }
  for(bucle=0; bucle<=sizeof(definir_pusadores)/sizeof(definir_pusadores[0]);bucle++){
    pinMode(definir_pusadores[bucle], INPUT);
  }
  for(bucle=0; bucle<=sizeof(definir_led_aviso)/sizeof(definir_led_aviso[0]);bucle++){
    pinMode(definir_led_aviso[bucle], INPUT);
  }
  imprimir(0);
}

void disp(int number){
  switch(number){
    case 0:    imprimir(0);    break;
    case 1:    imprimir(1);    break;
    case 2:    imprimir(2);    break;
    case 3:    imprimir(3);    break;
    case 4:    imprimir(4);    break;
    case 5:    imprimir(5);    break;
    case 6:    imprimir(6);    break;
    case 7:    imprimir(7);    break;
    case 8:    imprimir(8);    break;
    case 9:    imprimir(9);    break; 
  }
}

//imprimir el numero en el led de 7 segmentos
void imprimir(int numero){
  for(int x=0;x<7;x++){
    digitalWrite(numero,n[numero][x]);
  }  
}


void loop() {
  bool pulsador_grabar;
  bool pulsador_up;
  bool pulsador_down;
  bool pulsador_ok;
  do{
     pulsador_up=digitalRead(definir_pusadores[0]);
     pulsador_down=digitalRead(definir_pusadores[1]);
     pulsador_grabar=digitalRead(definir_pusadores[2]);
     pulsador_ok=digitalRead(definir_pusadores[3]);

    //mover de numeros
    if(!pulsador_grabar||!pulsador_ok){
      pulsador_grabar=0;
      pulsador_ok=0;
    }
    //si no se presionan al mismo tiempo
    if(!pulsador_up||!pulsador_down){
      if(pulsador_up){
        numero_inicio--;
      }
      else{
        if(pulsador_down){
          numero_inicio++;
        }
      }
    }
    if(numero_inicio<0){
      numero_inicio=9;
    }
    
    if(numero_inicio>9){
      numero_inicio=0;
    }
    disp(numero_inicio);
    delay(250);
    //bucle hasta que se presione ok o grabar pero no ambos
  }while(!pulsador_grabar&&!pulsador_ok);
  if(pulsador_grabar){
    //codigo recibir y guardar IR
  }
  if(pulsador_ok){
    //codigo leer EEPROM y enviar IR
  }
}
