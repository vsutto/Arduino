/* Autor: Victor A. Sutto.
   Código desenvolvido para um teclado de calibração, sem tela de confirmação(usado na Assistência Técnica). Display = 128x64
   Salva os valores na EEPROM quando apertar o "Enter".
   Os botões "+" e "-" altera o valor de calibração a ser salvo.
   O botão "Menu" altera as telas(Tela cliente, Tela de calibração 1, Tela de calibração 2, Tela de calibração 3 e Tela de calibração 4. (volta a 1ª tela com mais um click)
*/


#include<ADS1115.h>
ADS1115 adc0 (ADS1115_DEFAULT_ADDRESS);
#include <Wire.h>
#include <EEPROM.h>
#include<U8glib.h>
U8GLIB_ST7920_128X64_1X u8g(4, 5, 6, 7); //Enable, RW, RS, RESET

//========== Conta 4 - 20 mA. ==========
int zero = 0 ;  // Valor para 4 mA.
int span = 4660 ; // Valor para 20 mA.
float indica = 0.0 ;
float indicaConv = 0.0 ;
float indicaConv1 = 0.0 ;
float conta = 0.0 ;
int saida = 0 ;


//========== Botões ==========
int cntClkMenu = 0 ; // Conta os cliques do menu para as paginas de calibração.
int bMenos; // Subtrai valores para a calibração.
int bMais; // Soma valores para a calibração.
int bEnter; // Salva valores para a calibração.
int ebtMenu; // Estado do botao (high or low) do menu pra digitalRead.

//========== delay dos botões ==========
unsigned long lastDebounceTime = 10 ; // Ultima vez que os botões foram apertados.
unsigned long debounceDelay = 10 ; // O intervalo, igual ao delay do código anterior.

//========== EEPROM ==========
int cntClkTL1 = 0 ; // Armazena o valor de calibração da pagina 1.
int cntClkTL2 = 0 ; // Armazena o valor de calibração da pagina 2.
int cntClkTL3 = 0 ; // Armazena o valor de calibração da pagina 3.
int cntClkTL4 = 0 ; // Armazena o valor de calibração da pagina 4.

int address1 = 1 ; // Variavel Local de memória da EEPROM pra tela de calibração 1.
int address2 = 2 ; // Variavel Local de memoria da EEPROM pra tela de calibração 2.
int address3 = 3 ; // Variavel Local de memoria da EEPROM pra tela de calibração 3.
int address4 = 4 ; // Variavel Local de memória da EEPROM pra tela de calibração 4.

int value1 = EEPROM.read(address1) ;
int value2 = EEPROM.read(address2) ;
int value3 = EEPROM.read(address3) ;
int value4 = EEPROM.read(address4) ;

void (*funcReset)() = 0 ; //========== Função que "aperta o reset" (Ele só atualizava a EEPROM quando resetava). ==========

void u8g_prepare() //========== Prepara a tela. ==========
{ 
 u8g.setFont(u8g_font_ncenB10);
 u8g.setFontRefHeightExtendedText();
 u8g.setDefaultForegroundColor();
 u8g.setColorIndex(1);
 u8g.drawRFrame(0, 0, 128, 64, 3); //moldura
}


void Contas() //========== Conta 4 - 20 mA. ==========
{
 adc0.setMultiplexer(ADS1115_MUX_P0_NG);
 adc0.getConversion();
 indicaConv1 = adc0.getMilliVolts();
 indicaConv = indicaConv1 ; // se for de 0 a 10% = "/ 10.0" ;

 conta = ((indicaConv - zero) * 99.99 / (span - zero)) ;
 
 delay (200) ;

}

void Tela0() //========== Tela Cliente. ==========
{
 u8g.setPrintPos(5, 38);
 u8g.print("TELA CLIENTE");
}


void Tela1()
{
   u8g.setPrintPos(114, 16); //========== Numeração das paginas. ========== 
   u8g.print("1");
   u8g.drawCircle(117, 10, 8); // Circulo.
    
   u8g.setPrintPos(86, 17); 
   u8g.print(cntClkTL1);
   u8g.setPrintPos(2, 17);
   u8g.print("cntClkTL1:");
  
   u8g.setPrintPos(74, 38);
   u8g.print(value1);
   u8g.setPrintPos(2, 38);
   u8g.print("e2prom1:"); 
  
   u8g.setPrintPos(2, 60);
   u8g.print("Conta:        %");
 if ( conta > 9.95 ) {  
   u8g.setPrintPos(53, 60);
   u8g.print(conta, 1);
 } else { 
   u8g.setPrintPos(61, 60);
   u8g.print(conta, 1);
 }
}

void Tela2()
{ 
   u8g.setPrintPos(114, 16); //========== Numeração das paginas. ========== 
   u8g.print("2");
   u8g.drawCircle(117, 10, 8); // Circulo.
      
   u8g.setPrintPos(86, 17);
   u8g.print(cntClkTL2);
   u8g.setPrintPos(2, 17);
   u8g.print("cntClkTL2:");
  
   u8g.setPrintPos(74, 38);
   u8g.print(value2);
   u8g.setPrintPos(2, 38);
   u8g.print("e2prom2:");
  
   u8g.setPrintPos(2, 60);
   u8g.print("Conta:        %");
 if ( conta > 9.95 ) {  
   u8g.setPrintPos(53, 60);
   u8g.print(conta, 1);
 } else {
   u8g.setPrintPos(61, 60);
   u8g.print(conta, 1);
 }
}

void Tela3()
{ 
   u8g.setPrintPos(114, 16); //========== Numeração das paginas. ==========   
   u8g.print("3");
   u8g.drawCircle(117, 10, 8); // Circulo.
      
   u8g.setPrintPos(86, 17);
   u8g.print(cntClkTL3);
   u8g.setPrintPos(2, 17);
   u8g.print("cntClkTL3:");
  
   u8g.setPrintPos(74, 38);
   u8g.print(value3);
   u8g.setPrintPos(2, 38);
   u8g.print("e2prom3:"); 
  
   u8g.setPrintPos(2, 60);
   u8g.print("Conta:        %");
 if ( conta > 9.95 )  {
   u8g.setPrintPos(53, 60);
   u8g.print(conta, 1);
 } else {
   u8g.setPrintPos(61, 60);
   u8g.print(conta, 1);
 }
}

void Tela4()
{
   u8g.setPrintPos(114, 16); //========== Numeração das paginas. ==========  
   u8g.print("4");
   u8g.drawCircle(117, 10, 8); // Circulo.
      
   u8g.setPrintPos(86, 17);
   u8g.print(cntClkTL4);
   u8g.setPrintPos(2, 17);
   u8g.print("cntClkTL4:");
  
   u8g.setPrintPos(74, 38);
   u8g.print(value4);
   u8g.setPrintPos(2, 38);
   u8g.print("e2prom4:");
  
   u8g.setPrintPos(2, 60);
   u8g.print("Conta:        %");
 if (conta > 9.95) {
   u8g.setPrintPos(53, 60);
   u8g.print(conta, 1);
 } else {
   u8g.setPrintPos(61, 60);
   u8g.print(conta, 1);
 }
}


void Limitador()
{
 if (cntClkMenu > 4)  cntClkMenu = 0 ;

 if (cntClkTL1 < 0)  cntClkTL1 = 100 ;
 if (cntClkTL1 > 100) cntClkTL1 = 0 ;  
 if (cntClkTL2 < 0)  cntClkTL2 = 100 ;
 if (cntClkTL2 > 100) cntClkTL2 = 0 ; 
 if (cntClkTL3 < 0)  cntClkTL3 = 100 ;
 if (cntClkTL3 > 100) cntClkTL3 = 0 ;
 if (cntClkTL4 < 0)  cntClkTL4 = 100 ;
 if (cntClkTL4 > 100) cntClkTL4 = 0 ;

 if (conta < 0)  conta = 0 ;
 if (conta > 99.95) conta = 99.9 ;  
}


void btMenu() 
{
 int ebtMenu = digitalRead(14); // Verifica se o botão foi pressionado.
  if (ebtMenu == LOW) {
  if ((millis() - lastDebounceTime) > debounceDelay) {
     cntClkMenu++ ;
  }
     lastDebounceTime = millis();
  }
}

void btMenos()
{
 int ebtMenos = digitalRead(15); // Verifica se o botão foi pressionado.
  if (ebtMenos == LOW && cntClkMenu == 1) {
  if ((millis() - lastDebounceTime) > debounceDelay) {
     cntClkTL1-- ;
  }
     lastDebounceTime = millis();
  }
  
  if (ebtMenos == LOW && cntClkMenu == 2) {
     ((millis() - lastDebounceTime) > debounceDelay) ;
     cntClkTL2-- ;
  }
   
  if (ebtMenos == LOW && cntClkMenu == 3) {
     ((millis() - lastDebounceTime) > debounceDelay) ;
     cntClkTL3-- ;
  }
  
  if (ebtMenos == LOW && cntClkMenu == 4) {
     ((millis() - lastDebounceTime) > debounceDelay) ;
     cntClkTL4-- ;
  }
}

void btMais() 
{
 int ebtMais = digitalRead(16);
  if (ebtMais == LOW && cntClkMenu == 1) {
     ((millis() - lastDebounceTime) > debounceDelay);
     cntClkTL1++;
  }
     lastDebounceTime = millis();
     
  if (ebtMais == LOW && cntClkMenu == 2) {
     ((millis() - lastDebounceTime) > debounceDelay) ;
     cntClkTL2++;
  }
    
  if (ebtMais == LOW && cntClkMenu == 3) {
     ((millis() - lastDebounceTime) > debounceDelay) ;
     cntClkTL3++;
  }   
    
  if (ebtMais == LOW && cntClkMenu == 4) {
     ((millis() - lastDebounceTime) > debounceDelay) ;
     cntClkTL4++;
  } 
}

void btEnter() 
{
 int bEnter = digitalRead(17) ;
  if (bEnter == LOW && cntClkMenu == 1) {
     ((millis() - lastDebounceTime) > debounceDelay);
     EEPROM.write(address1, cntClkTL1);
     Serial.println("Enter Tela1");
     cntClkMenu++;
     funcReset();
  }
 
  if (bEnter == LOW && cntClkMenu == 2) {
     ((millis() - lastDebounceTime) > debounceDelay);
     EEPROM.write(address2, cntClkTL2);
     Serial.println("Enter Tela2");
     cntClkMenu++;
     funcReset();
  }

  if (bEnter == LOW && cntClkMenu == 3) {
     ((millis() - lastDebounceTime) > debounceDelay) ;
     EEPROM.write(address3, cntClkTL3);
     Serial.println("Enter Tela3");
     cntClkMenu++;
     funcReset();
  }
   
  if (bEnter == LOW && cntClkMenu == 4) {
     ((millis() - lastDebounceTime) > debounceDelay) ;
     EEPROM.write(address4, cntClkTL4);
     Serial.println("Enter Tela4");
     cntClkMenu++;
     funcReset();
  }
}

  
void Telas() 
{ 
 u8g_prepare();
  switch (cntClkMenu){
  case 0: Tela0();
  break;
  
  case 1: Tela1();
  break;
  
  case 2: Tela2();
  break;
  
  case 3: Tela3();
  break;
  
  case 4: Tela4();
  break;
  }
}


void setup() 
{
   Serial.begin(115200);
   Wire.begin();
  
 for (int i = 14; i < 18; i++) pinMode(i, INPUT_PULLUP); //========== Declarando os pinos como INPUT_PULLUP ==========

   adc0.initialize();
   adc0.setMode(ADS1115_MODE_SINGLESHOT);
   adc0.setRate(ADS1115_RATE_8);
   adc0.setGain(ADS1115_PGA_6P144);
}

void loop()
{
 u8g.firstPage();
 do Telas();
 while(u8g.nextPage());
 
 Tela0();
 Tela1();
 Tela2();
 Tela3();
 Tela4();


 Contas();
 Limitador();

 btMenu();
 btMenos();
 btMais();
 btEnter();

 delay(1);
}
