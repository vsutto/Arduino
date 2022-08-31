/* Código desenvolvido mais para consolidar meu conhecimento no "Front-end" do arduino.
   Contém 3 janelas, com marcador de janelas e ajustador de casas decimais.
*/

#include <U8glib.h>
U8GLIB_ST7920_128X64_1X u8g(4, 5, 6, 7); //Enable, RW, RS, RESET


#include <Adafruit_ADS1X15.h>
#include <Wire.h>

    float mV = 0.00;

    Adafruit_ADS1115 ads;
    const float multiplier = 0.1875F;


// declarando as variáveis
    const int botao = 3; // porta usada para o botao
 
    int eBotao; // verifica o estado do botão
    int cntPag = 1;  // conta os clicks para as páginas
    int cntClicks = 0; // conta os clicks botao
    int un = 0; // clicks de 10 em 10
 

    unsigned long lastDebounceTime = 100; // última vez que o botão foi pressionado
    unsigned long debounceDelay = 200;   // O intervalo, igual ao delay do código anterior


void u8g_prepare() // prepara o display =======================================================================================================
{
    u8g.setFont(u8g_font_7x13B);
    u8g.setFontRefHeightExtendedText();
    u8g.setDefaultForegroundColor();
    u8g.setColorIndex(1);
  
}


void Tela1(){
   if (cntPag == 1){
      u8g.setPrintPos(116,60);              // } numeraçao de paginas 
      u8g.print("1");
      u8g.drawCircle(119, 55, 8); // circulo

      u8g.setPrintPos(7,60);
      u8g.print("UN.:");


      u8g.setPrintPos(7,40);
      u8g.print("Tensao:");
      u8g.setPrintPos(57,40);
      u8g.print(mV);
      u8g.setPrintPos(93,40);
      u8g.print("%");


   if (eBotao == LOW) {
   if (un >= 0 && un < 10) {
      u8g.setPrintPos(56,60);
      u8g.print(un);
      } else {
     }
    }

    if (eBotao == LOW) {
    if (un > 9 && un < 100) {
       u8g.setPrintPos(49,60);
       u8g.print(un);
        } else {
       }
      }
      
     if (eBotao == LOW) {
     if (un > 99 && un < 1000) {
        u8g.setPrintPos(42,60);
        u8g.print(un);
        } else {
       }
      }

      if (eBotao == LOW) {
     if (un > 999 && un < 10000) {
        u8g.setPrintPos(35,60);
        u8g.print(un);
        } else {
       }
      }
     
     u8g.setPrintPos(47,22);
     u8g.print(cntClicks);
     u8g.setPrintPos(7,20);
     u8g.print("Clk.:");
     u8g.drawRFrame(41,7,25,20, 3); // borda Nº clicks
     
     u8g.drawRFrame(0,0,128,64, 9); // moldura
     
  }  
}



void Tela2(){
  if (cntPag == 2){
     u8g.setPrintPos(116,60);   // } numeraçao de paginas
     u8g.print("2");
     u8g.drawCircle(119, 55, 8); // circulo

     u8g.setPrintPos(7,60);
     u8g.print("UN.:");


     u8g.setPrintPos(7,40);
     u8g.print("Tensao:");
     u8g.setPrintPos(57,40);
     u8g.print(mV);
     u8g.setPrintPos(93,40);
     u8g.print("%");

     
    if (eBotao == LOW) {
   if (un >= 0 && un < 10) {
      u8g.setPrintPos(56,60);
      u8g.print(un);
      } else {
     }
    }

    if (eBotao == LOW) {
    if (un > 9 && un < 100) {
       u8g.setPrintPos(49,60);
       u8g.print(un);
        } else {
       }
      }
      
     if (eBotao == LOW) {
     if (un > 99 && un < 1000) {
        u8g.setPrintPos(42,60);
        u8g.print(un);
        } else {
       }
      }

     if (eBotao == LOW) {
     if (un > 999 && un < 10000) {
        u8g.setPrintPos(35,60);
        u8g.print(un);
        } else {
       }
      }
     

    u8g.setPrintPos(47,22);
     u8g.print(cntClicks);
     u8g.setPrintPos(7,20);
     u8g.print("Clk.:");
     u8g.drawRFrame(41,7,25,20, 3); // borda Nº clicks
    
     u8g.drawRFrame(0,0,128,64, 9); // moldura
     
    } 
   }

      
void Tela3(){
  if (cntPag == 3){    
     u8g.setPrintPos(116,60);  // } numero de paginas
     u8g.print("3");
     u8g.drawCircle(119, 55, 8); // circulo

     u8g.setPrintPos(7,60);
     u8g.print("UN.:");


     u8g.setPrintPos(7,40);
     u8g.print("Tensao:");
     u8g.setPrintPos(57,40);
     u8g.print(mV);
     u8g.setPrintPos(93,40);
     u8g.print("%");

     
   if (eBotao == LOW) {
   if (un >= 0 && un < 10) {
      u8g.setPrintPos(56,60);
      u8g.print(un);
      } else {
     }
    }

    if (eBotao == LOW) {
    if (un > 9 && un < 100) {
       u8g.setPrintPos(49,60);
       u8g.print(un);
        } else {
       }
      }
      
     if (eBotao == LOW) {
     if (un > 99 && un < 1000) {
        u8g.setPrintPos(42,60);
        u8g.print(un);
        } else {
       }
      }

     if (eBotao == LOW) {
     if (un > 999 && un < 10000) {
        u8g.setPrintPos(35,60);
        u8g.print(un);
        } else {
       }
      }

     u8g.setPrintPos(47,22);
     u8g.print(cntClicks);
     u8g.setPrintPos(7,20);
     u8g.print("Clk.:");
     u8g.drawRFrame(41,7,25,20, 3); // borda Nº clicks
     
     u8g.drawRFrame(0,0,128,64, 9); // moldura
     
  }
}


void draw() // Rotina Desenho
{
    u8g_prepare();  
    Tela1();
    Tela2();
    Tela3();   
} 


void setup() {
    Serial.begin(9600);
    pinMode(botao, INPUT_PULLUP); //configura a entrada 3 pro botão
    ads.begin();
}


void loop(){
         u8g.firstPage();
      do 
        {
         draw ();
        }
         while( u8g.nextPage());

         int eBotao = digitalRead(14); // verifica se o botão foi pressionado

      if (eBotao == LOW) {
      if ((millis() - lastDebounceTime) > debounceDelay) {
         cntPag++; 
         cntClicks++;
         
         if (cntClicks >= 0 && cntClicks <= 10) {
         un += 1;
         }

         if (cntClicks > 10 && cntClicks < 20) {
         un += 10;
         }

         if (cntClicks > 19 && cntClicks < 29) {
         un += 100;
         }

         if (cntClicks > 28 && cntClicks < 38) {
         un += 1000;
         }
         
         lastDebounceTime = millis();
      }
     }

        if (un > 9000) {
          un = 0;
          }

      if (cntPag == 4) {
         cntPag = 1;
      }

      if (cntClicks > 36) {
         cntClicks = 0;
      }

     
      int16_t adc0;
      adc0 = ads.readADC_SingleEnded(0);
      Serial.print("AIN0: "); Serial.println(adc0 * multiplier);
      Serial.println(mV);
      mV = ((adc0 * multiplier) / 5000) * 100;
     
      Serial.println();
      millis();

       Serial.println("botao:");  Serial.println(eBotao);
       Serial.println("pagina:");  Serial.println(cntPag);
       Serial.println("millis:");  Serial.println(millis());
       Serial.println("clicks:");  Serial.println(cntClicks);
       Serial.println();
       Serial.println();
       Serial.println();
      
  
 
}  
