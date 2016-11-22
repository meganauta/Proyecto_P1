#include <IRremote.h>  //librerias para el IR
IRsend irsend; //Configurado por la libreria (en arduino mega 2560 esta en el pin 9
IRrecv irrecv(10);

//Encendido y apagado de el led de 7 segmentos
bool n[12][4]={ {0,0,0,0},
              {0,0,0,1},
              {0,0,1,0},
              {0,0,1,1},
              {0,1,0,0},
              {0,1,0,1},
              {0,1,1,0},
              {0,1,1,1},
              {1,0,0,0},
              {1,0,0,1},
              {1,1,1,0},
              {1,1,1,1} };
                

//pines que se usan
int definir_pines_led_display[]={36,37,38,39};
int definir_pusadores[]={27,28,29,30};
int bucle;
int numero_inicio=0;


//Almacenar los datos que llegaron
unsigned long codigo_IR[10][3];

//configuracon global
void setup() {
  // put your setup code here, to run once:
  irrecv.enableIRIn();
  for(bucle=0; bucle<sizeof(definir_pines_led_display)/sizeof(definir_pines_led_display[0]);bucle++){
    pinMode(definir_pines_led_display[bucle], OUTPUT);
  }
  for(bucle=0; bucle<sizeof(definir_pusadores)/sizeof(definir_pusadores[0]);bucle++){
    pinMode(definir_pusadores[bucle], INPUT);
  }
  for(bucle=0;bucle<sizeof(codigo_IR)/sizeof(codigo_IR[0]);bucle++){
    codigo_IR[bucle]=0;
  }
    disp(numero_inicio);
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
  for(int x=0;x<4;x++){
    digitalWrite(definir_pines_led_display[x],n[numero][x]);
  }  
}

int decodificando (decode_results *results){
  if(results->overflow){
    return -1;
  }
  switch (results->decode_type) {
    default:
    case UNKNOWN:      /*Serial.print("UNKNOWN");*/       return -1;    break ;
    case NEC:          /*Serial.print("NEC");*/           return 0;    break ;
    case SONY:         /*Serial.print("SONY");*/          return 1;    break ;
    case RC5:          /*Serial.print("RC5");*/           return 2;    break ;
    case RC6:          /*Serial.print("RC6");*/           return 3;    break ;
    case DISH:         /*Serial.print("DISH");*/          return 4;    break ;
    case SHARP:        /*Serial.print("SHARP");*/         return 5;    break ;
    case JVC:          /*Serial.print("JVC");*/           return 6;    break ;
    case SANYO:        /*Serial.print("SANYO");*/         return 7;    break ;
    case MITSUBISHI:   /*Serial.print("MITSUBISHI");*/    return 8;    break ;
    case SAMSUNG:      /*Serial.print("SAMSUNG"); */      return 9;    break ;
    case LG:           /*Serial.print("LG");  */          return 10;    break ;
    case WHYNTER:      /*Serial.print("WHYNTER"); */      return 11;    break ;
    case AIWA_RC_T501: /*Serial.print("AIWA_RC_T501"); */ return 12;    break ;
    case PANASONIC:    /*Serial.print("PANASONIC");  */   return 13;    break ;
    case DENON:        /*Serial.print("Denon");    */     return 14;    break ;
  }
  return -1;
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

    //si los botones estan aplastados al mismo tiempo
    if(!pulsador_grabar||!pulsador_ok){
      pulsador_grabar=0;
      pulsador_ok=0;
    }
    if(!pulsador_up||!pulsador_down){
      
      //Aumentar o disminuir la cifra
      if(pulsador_up){
        numero_inicio++;
      }
        if(pulsador_down){
          numero_inicio--;
      }
    }
    //Si se pasa los limites se posiciona al comienzo o al final
    if(numero_inicio<0){
      numero_inicio=9;
    }
    
    if(numero_inicio>9){
      numero_inicio=0;
    }
    //Se muetran resultados
    disp(numero_inicio);
    delay(250);
    //bucle hasta que se presione ok o grabar pero no ambos
  }while(!pulsador_grabar&&!pulsador_ok);
  if(pulsador_grabar){
    //codigo recibir y guardar IR
    disp(11);
    do{
    decode_results  results;
    }while(!irrecv.decode(&results))//decode devuelbe true o flase si ingreso un pulso IR y si es valido
    if(decodificando(&results)<0){
      disp(10);
      delay(650);
      disp(11);
      delay(250);
      disp(10);
      delay(650);
      disp(11);
      delay(250);
    }
    else{
      disp(numero_inicio);
      codigo_IR[numero_inicio][0]=decodificando(&results);
      if(decodificando(&results)==13){
         codigo_IR[numero_inicio][1]=results->address;
         codigo_IR[numero_inicio][2]=results->value;
      }
      else{
        codigo_IR[numero_inicio][1]=results->value;
        codigo_IR[numero_inicio][2]=results->results->bits;
      }
    }
    disp(numero_inicio);
  }
  if(pulsador_ok){
    //codigo leer EEPROM y enviar IR
  }
}
