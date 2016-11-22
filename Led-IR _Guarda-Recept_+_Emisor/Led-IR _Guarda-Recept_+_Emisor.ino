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
  irrecv.enableIRIn(); // Start the receiver
  for(bucle=0; bucle<sizeof(definir_pines_led_display)/sizeof(definir_pines_led_display[0]);bucle++){
    pinMode(definir_pines_led_display[bucle], OUTPUT);
  }
  for(bucle=0; bucle<sizeof(definir_pusadores)/sizeof(definir_pusadores[0]);bucle++){
    pinMode(definir_pusadores[bucle], INPUT);
  }
  for(int x=0;x<3;x++){
    for(bucle=0;bucle<10;bucle++){
    codigo_IR[bucle][x]=-1;
    }
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

void decodificando (decode_results *results){
  if(results->overflow){
      disp(10);
      delay(650);
      disp(11);
      delay(250);
      disp(10);
      delay(650);
      disp(11);
      delay(250);
  }
  switch (results->decode_type) {
    default:          disp(10);
      delay(650);
      disp(11);
      delay(250);
      disp(10);
      delay(650);
      disp(11);
      delay(250);     break ;
    case UNKNOWN:      /*Serial.print("UNKNOWN");*/    disp(10);
      delay(650);
      disp(11);
      delay(250);
      disp(10);
      delay(650);
      disp(11);
      delay(250);    break ;
    case NEC:          /*Serial.print("NEC");*/    codigo_IR[numero_inicio][0]=0;  codigo_IR[numero_inicio][1]=results->value;         codigo_IR[numero_inicio][2]=results->bits;         break ;
    case SONY:         /*Serial.print("SONY");*/   codigo_IR[numero_inicio][0]=1;  codigo_IR[numero_inicio][1]=results->value;         codigo_IR[numero_inicio][2]=results->bits;         break ;
    case RC5:          /*Serial.print("RC5");*/    codigo_IR[numero_inicio][0]=2;  codigo_IR[numero_inicio][1]=results->value;         codigo_IR[numero_inicio][2]=results->bits;         break ;
    case RC6:          /*Serial.print("RC6");*/    codigo_IR[numero_inicio][0]=3;  codigo_IR[numero_inicio][1]=results->value;         codigo_IR[numero_inicio][2]=results->bits;         break ;
    case DISH:         /*Serial.print("DISH");*/   codigo_IR[numero_inicio][0]=4;  codigo_IR[numero_inicio][1]=results->value;         codigo_IR[numero_inicio][2]=results->bits;         break ;
    case SHARP:        /*Serial.print("SHARP");*/  codigo_IR[numero_inicio][0]=5;  codigo_IR[numero_inicio][1]=results->value;         codigo_IR[numero_inicio][2]=results->bits;         break ;
    case JVC:          /*Serial.print("JVC");*/    codigo_IR[numero_inicio][0]=6;  codigo_IR[numero_inicio][1]=results->value;         codigo_IR[numero_inicio][2]=results->bits;         break ;
  /*case SANYO:         Serial.print("SANYO");            return 7;    break ;*/
  /*  case MITSUBISHI:   Serial.print("MITSUBISHI");    return 8;    break ;*/
    case SAMSUNG:   /*Serial.print("SAMSUNG"); */  codigo_IR[numero_inicio][0]=9;  codigo_IR[numero_inicio][1]=results->value;         codigo_IR[numero_inicio][2]=results->bits;         break ;
    case LG:           /*Serial.print("LG");  */   codigo_IR[numero_inicio][0]=10;  codigo_IR[numero_inicio][1]=results->value;         codigo_IR[numero_inicio][2]=results->bits;        break ;
    case WHYNTER:      /*Serial.print("WHYNTER"); */ codigo_IR[numero_inicio][0]=11;  codigo_IR[numero_inicio][1]=results->value;         codigo_IR[numero_inicio][2]=results->bits;        break ;
    case AIWA_RC_T501: /*Serial.print("AIWA_RC_T501"); */ codigo_IR[numero_inicio][0]=12;  codigo_IR[numero_inicio][1]=results->value;         codigo_IR[numero_inicio][2]=results->bits;   break ;
    case PANASONIC:    /*Serial.print("PANASONIC");  */codigo_IR[numero_inicio][0]=13;  codigo_IR[numero_inicio][1]=results->address;         codigo_IR[numero_inicio][2]=results->value;   break ;
    case DENON:        /*Serial.print("Denon");    */    codigo_IR[numero_inicio][0]=14;  codigo_IR[numero_inicio][1]=results->value;         codigo_IR[numero_inicio][2]=results->bits;    break ;
  }
}








void codificando (int x_value){
  switch (x_value) {
    case 0:          /*Serial.print("NEC");*/
                     irsend.sendNEC(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2]);
    break ;
    case 1:         /*Serial.print("SONY");*/ 
                     irsend.sendSony(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2]);
    break ;
    case 2:          /*Serial.print("RC5");*/ 
                     irsend.sendRC5(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2]);                   
    break ;
    case 3:          /*Serial.print("RC6");*/ 
                     irsend.sendRC6(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2]);    
    break ;
    case 4:         /*Serial.print("DISH");*/
                     irsend.sendDISH(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2]);
    break ;
    case 5:        /*Serial.print("SHARP");*/  
                     irsend.sendSharp(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2]);    
    break ;
    case 6:          /*Serial.print("JVC");*/  
                      irsend.sendJVC(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2],0);   
    break ;
    /*case 7:        Serial.print("SANYO");
                     irsend.sendSANYO(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2]);  
    break ;*/
    /*case 8:   /*Serial.print("MITSUBISHI");*/ 
    //                  irsend.sendMITSUBISHI(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2]); 
   // break ;
    case 9:      /*Serial.print("SAMSUNG"); */  
                      irsend.sendSAMSUNG(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2]);
    break ;
    case 10:           /*Serial.print("LG");  */            
                         irsend.sendLG(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2]);
    break ;
    case 11:      /*Serial.print("WHYNTER"); */         
                         irsend.sendWhynter(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2]);
    break ;
    case 12: /*Serial.print("AIWA_RC_T501"); */       
                         irsend.sendAiwaRCT501(codigo_IR[numero_inicio][1]);
    break ;
    case 13:    /*Serial.print("PANASONIC");  */    
                         irsend.sendPanasonic(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2]);
    break ;
    case 14:        /*Serial.print("Denon");    */   
                         irsend.sendDenon(codigo_IR[numero_inicio][1],codigo_IR[numero_inicio][2]);
    break ;
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
    decode_results  results;
    do{
    decode_results  results;
    }while(!irrecv.decode(&results));//decode devuelbe true o flase si ingreso un pulso IR y si es valido
    
      disp(numero_inicio);
      decodificando(&results);
      delay(150);
      disp(11);
      delay(150);
    }
    //podria ingresarse codigo para guardar los datos en la EEPROM
  if(pulsador_ok){
    //codigo leer y enviar IR
    if(codigo_IR[numero_inicio][0]<0){
      disp(10);
      delay(150);
      disp(11);
      delay(750);
    }
    else{
      codificando(codigo_IR[numero_inicio][0]);
      disp(numero_inicio);
      delay(150);
      disp(11);
      delay(150);
    }
  }
  disp(numero_inicio);
  irrecv.resume();
}
