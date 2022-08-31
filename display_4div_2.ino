// Autor: Victor A. Sutto.
// Desenvolvido pra um painel de 3 gases.

#include <U8glib.h>
U8GLIB_ST7920_128X64_1X u8g(4, 5, 6, 7); //Enable, RW, RS, RESET

#include <ADS1115.h>
ADS1115 adc0(ADS1115_DEFAULT_ADDRESS);

// =========== colocar valores aqui ====================

float zeroVoltsG1 =   1 ;  // valor para G1 - 4mA  // ========== Gas 1 ==========
float maxVoltsG1  =  4730.0 ;  // valor para 100%      

float zeroVoltsG2 =   1 ;  // valor para G2 - 4mA  // ========== Gas 2 ==========
float maxVoltsG2  =  4730.0 ;  // valor para 100%       

float zeroVoltsG3 =   1 ;  // valor para G3 - 4mA  // ========== Gas 3 ==========
float maxVoltsG3  =  4730.0 ;  // valor para 100%       - 20mA

//======================================================

float valminG1  =   0.00 ;
float valmaxG1  = 100.00 ;
float convG1    =   0.00 ;
float contaG1   =   0.00 ;
float indicaG1  =   0.00 ;

float valmiNG2  =   0.00 ;
float valmaxG2  = 100.00 ;
float convG2    =   0.00 ;
float contaG2   =   0.00 ;
float indicaG2  =   0.00 ;

float valminG3  =   0.00 ;
float valmaxG3  = 100.00 ;
float convG3    =   0.00 ;
float contaG3   =   0.00 ;
float indicaG3  =   0.00 ;



float G1 = 0.00 ;
float G2 = 0.00 ;
float G3 = 0.00 ;

void u8g_prepare() // prepara o display =======================================================================================================
{
  u8g.setFont(u8g_font_ncenB12);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setColorIndex(1);

}


void u8g_Tela() // formata a Tela
{   
  u8g.drawRFrame(0,0,128,64,3); // moldura

  u8g.drawStr( 6, 14, "G1  :             ppm");
  u8g.drawStr( 2, 30 , "G2:             ppm" );
  u8g.drawStr( 3, 46 , "G3:             ppm" );


  
  u8g.drawLine(0,16,128,16);
  u8g.drawLine(0,32,128,32);
  u8g.drawLine(0,48,128,48);

  u8g.drawLine(43,0,43,64);
  u8g.drawLine(85,0,85,64);
 


//=============== posicao das casas G1 ================================================================================================================
  
  if (G1 >= 0 && G1 < 9.5){ 
    u8g.setPrintPos(73,14);
    u8g.print(G1,0);
  }else{ 
    u8g.setPrintPos(65,14);
    u8g.print(G1,0);
}  

//=============== posicao das casas G2 ===============================================================================================================

  if (G2 >= 0 && G2 < 9.5) {
    u8g.setPrintPos(73,30);
    u8g.print(G2,0);
  }else{ 
    u8g.setPrintPos(65,30);
    u8g.print(G2,0);
} 
      
//=============== posicao das casas G3 ===============================================================================================================
 
  if (G3 >= 0 && G3 < 9.5) {
      u8g.setPrintPos(73,46);
      u8g.print(G3,0);
   } else {
      u8g.setPrintPos(65,46);
      u8g.print(G3,0);
  }     
//=============== numeros pequenos ===========================================================================================================
   
    u8g.setFont(u8g_font_ncenB08);
    u8g.drawStr( 28, 15, "2");
}


void draw() // Rotina Desenho
{
    u8g_prepare();  
    u8g_Tela();  
} 

void setup() {
  Wire.begin();
  Serial.begin(9600);
  
// inicia ads

  adc0.initialize();
  adc0.setMode(ADS1115_MODE_SINGLESHOT);
  adc0.setRate(ADS1115_RATE_8);
  adc0.setGain(ADS1115_PGA_6P144);
  
}

void loop() {
    u8g.firstPage();
  do 
{
    draw ();
}
    while( u8g.nextPage());


     G1 = contaG1 ;
     G2 = contaG2 ;
     G3 = contaG3 ;

//========== limite das variaveis ============================================================================================================
  if (G1 > 50) 
    G1 = 50;
  if (G2 > 50) 
    G2 = 50;
  if (G3 > 20) 
    G3 = 20;
    
//========== limite negativos das variaveis ==============================================================================================
  if (G1 < 0) 
    G1 = 0;
  if (G2 < 0) 
    G2 = 0;
  if (G3 < 0) 
    G3 = 0;

//========== contas ==========================================================================================================================
  
//========== G1 conta ==========
  adc0.setMultiplexer(ADS1115_MUX_P0_NG);
  adc0.getConversion();
  adc0.setRate(ADS1115_RATE_8);
  convG1 = adc0.getMilliVolts();

contaG1 = ((( convG1 - zeroVoltsG1 ) * ( valmaxG1 - valminG1 )) / ( maxVoltsG1 - zeroVoltsG1 )) + valminG1 ;
 
  if (contaG1 <= 0.0)
    indicaG1 = 0.0;
  else if (contaG1 >= 99.9)
    indicaG1 = 99.9;
  else
    indicaG1 = contaG1;

//========== G2 conta ==========

  adc0.setMultiplexer(ADS1115_MUX_P0_NG);
  adc0.getConversion();
  adc0.setRate(ADS1115_RATE_8);
  convG2 = adc0.getMilliVolts();

  contaG2 = ((( convG2 - zeroVoltsG2 ) * ( valmaxG2 - valminG2 )) / ( maxVoltsG2 - zeroVoltsG2 )) + valminG2 ;
 
  if (contaG2 <= 0.0)
    indicaG2 = 0.0;
  else if (contaG2 >= 99.9)
    indicaG2 = 99.9;
  else
    indicaG2 = contaG2;

//========== G3 conta ==========

  adc0.setMultiplexer(ADS1115_MUX_P0_NG);
  adc0.getConversion();
  adc0.setRate(ADS1115_RATE_8);
  convG3 = adc0.getMilliVolts();

  contaG3 = ((( convG3 - zeroVoltsG3 ) * ( valmaxG3 - valminG3 )) / ( maxVoltsG3 - zeroVoltsG3 )) + valminG3 ;
 
  if (contaG3 <= 0.0)
    indicaG3 = 0.0;
  else if (contaG3 >= 99.9)
    indicaG3 = 99.9;
  else
    indicaG3 = contaG3;
    
  Serial.print("ValorG1 = ")  ; Serial.println(convG1)  ;
  Serial.print("contaG1 = ")  ; Serial.println(contaG1) ;
  Serial.print("IndicaG1 = ") ; Serial.println(indicaG1);
  Serial.println();
  Serial.println();

  Serial.print("ValorG2 = ")  ; Serial.println(convG2)  ;
  Serial.print("contaG2 = ")  ; Serial.println(contaG2) ;
  Serial.print("IndicaG2 = ") ; Serial.println(indicaG2);
  Serial.println();
  Serial.println();

  Serial.print("ValorG3 = ")  ; Serial.println(convG3)  ;
  Serial.print("contaG3 = ")  ; Serial.println(contaG3) ;
  Serial.print("IndicaG3 = ") ; Serial.println(indicaG3);
  Serial.println();
  Serial.println();
  delay (500);
}
