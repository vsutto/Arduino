#include <U8glib.h>
U8GLIB_ST7920_128X64_1X u8g(4, 5, 6, 7); //Enable, RW, RS, RESET

#include <ADS1115.h>
ADS1115 adc0(ADS1115_DEFAULT_ADDRESS);

// =========== colocar valores aqui ====================

float zeroVoltsSO2 =   1 ;  // valor para SO2 - 4mA
float maxVoltsSO2  =  4730.0 ;  // valor para 100%       - 20mA

float zeroVoltsVOC =   1 ;  // valor para VOC - 4mA
float maxVoltsVOC  =  4730.0 ;  // valor para 100%       - 20mA

float zeroVoltsNOx =   1 ;  // valor para NOx - 4mA
float maxVoltsNOx  =  4730.0 ;  // valor para 100%       - 20mA

//======================================================

float valminSO2  =   0.00 ;
float valmaxSO2  = 100.00 ;
float convSO2    =   0.00 ;
float contaSO2   =   0.00 ;
float indicaSO2  =   0.00 ;

float valminVOC  =   0.00 ;
float valmaxVOC  = 100.00 ;
float convVOC    =   0.00 ;
float contaVOC   =   0.00 ;
float indicaVOC  =   0.00 ;

float valminNOx  =   0.00 ;
float valmaxNOx  = 100.00 ;
float convNOx    =   0.00 ;
float contaNOx   =   0.00 ;
float indicaNOx  =   0.00 ;



float SO2 = 0.00 ;
float VOC = 0.00 ;
float NOx = 0.00 ;

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

  u8g.drawStr( 6, 14, "SO  :             ppm");
  u8g.drawStr( 2, 30 , "VOC:             ppm" );
  u8g.drawStr( 3, 46 , "NOx:             ppm" );


  
  u8g.drawLine(0,16,128,16);
  u8g.drawLine(0,32,128,32);
  u8g.drawLine(0,48,128,48);

  u8g.drawLine(43,0,43,64);
  u8g.drawLine(85,0,85,64);
 


//=============== posicao das casas SO2 ================================================================================================================
  
  if (SO2 >= 0 && SO2 < 9.5){ 
    u8g.setPrintPos(73,14);
    u8g.print(SO2,0);
  }else{ 
    u8g.setPrintPos(65,14);
    u8g.print(SO2,0);
}  

//=============== posicao das casas VOC ===============================================================================================================

  if (VOC >= 0 && VOC < 9.5) {
    u8g.setPrintPos(73,30);
    u8g.print(VOC,0);
  }else{ 
    u8g.setPrintPos(65,30);
    u8g.print(VOC,0);
} 
      
//=============== posicao das casas NOx ===============================================================================================================
 
  if (NOx >= 0 && NOx < 9.5) {
      u8g.setPrintPos(73,46);
      u8g.print(NOx,0);
   } else {
      u8g.setPrintPos(65,46);
      u8g.print(NOx,0);
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


     SO2 = contaSO2 ;
     VOC = contaVOC ;
     NOx = contaNOx ;

//========== limite das variaveis ============================================================================================================
  if (SO2 > 50) 
    SO2 = 50;
  if (VOC > 50) 
    VOC = 50;
  if (NOx > 20) 
    NOx = 20;
    
//========== limite negativos das variaveis ==============================================================================================
  if (SO2 < 0) 
    SO2 = 0;
  if (VOC < 0) 
    VOC = 0;
  if (NOx < 0) 
    NOx = 0;

//========== contas ==========================================================================================================================
  
//========== SO2 conta ==========
  adc0.setMultiplexer(ADS1115_MUX_P0_NG);
  adc0.getConversion();
  adc0.setRate(ADS1115_RATE_8);
  convSO2 = adc0.getMilliVolts();

contaSO2 = ((( convSO2 - zeroVoltsSO2 ) * ( valmaxSO2 - valminSO2 )) / ( maxVoltsSO2 - zeroVoltsSO2 )) + valminSO2 ;
 
  if (contaSO2 <= 0.0)
    indicaSO2 = 0.0;
  else if (contaSO2 >= 99.9)
    indicaSO2 = 99.9;
  else
    indicaSO2 = contaSO2;

//========== VOC conta ==========

  adc0.setMultiplexer(ADS1115_MUX_P0_NG);
  adc0.getConversion();
  adc0.setRate(ADS1115_RATE_8);
  convVOC = adc0.getMilliVolts();

  contaVOC = ((( convVOC - zeroVoltsVOC ) * ( valmaxVOC - valminVOC )) / ( maxVoltsVOC - zeroVoltsVOC )) + valminVOC ;
 
  if (contaVOC <= 0.0)
    indicaVOC = 0.0;
  else if (contaVOC >= 99.9)
    indicaVOC = 99.9;
  else
    indicaVOC = contaVOC;

//========== NOx conta ==========

  adc0.setMultiplexer(ADS1115_MUX_P0_NG);
  adc0.getConversion();
  adc0.setRate(ADS1115_RATE_8);
  convNOx = adc0.getMilliVolts();

  contaNOx = ((( convNOx - zeroVoltsNOx ) * ( valmaxNOx - valminNOx )) / ( maxVoltsNOx - zeroVoltsNOx )) + valminNOx ;
 
  if (contaNOx <= 0.0)
    indicaNOx = 0.0;
  else if (contaNOx >= 99.9)
    indicaNOx = 99.9;
  else
    indicaNOx = contaNOx;
    
  Serial.print("ValorSO2 = ")  ; Serial.println(convSO2)  ;
  Serial.print("contaSO2 = ")  ; Serial.println(contaSO2) ;
  Serial.print("IndicaSO2 = ") ; Serial.println(indicaSO2);
  Serial.println();
  Serial.println();

  Serial.print("ValorVOC = ")  ; Serial.println(convVOC)  ;
  Serial.print("contaVOC = ")  ; Serial.println(contaVOC) ;
  Serial.print("IndicaVOC = ") ; Serial.println(indicaVOC);
  Serial.println();
  Serial.println();

  Serial.print("ValorNOx = ")  ; Serial.println(convNOx)  ;
  Serial.print("contaNOx = ")  ; Serial.println(contaNOx) ;
  Serial.print("IndicaNOx = ") ; Serial.println(indicaNOx);
  Serial.println();
  Serial.println();
  delay (500);
}
