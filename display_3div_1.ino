#include <ADS1115.h>
ADS1115 adc0(ADS1115_DEFAULT_ADDRESS);



#include <U8glib.h>
U8GLIB_ST7920_128X64_1X u8g(4, 5, 6, 7); //Enable, RW, RS, RESET

// =========== colocar valores aqui ==========================================================================================================

float zeroVoltsO2 =   1;  // valor para O2 - 4mA
float maxVoltsO2  =  4720.0 ;  // valor para 100%       - 20mA


float zeroVoltsCO =   1;  // valor para CO - 4mA
float maxVoltsCO  =  4720.0 ;  // valor para 100%       - 20mA


float zeroVoltsCO2 =   1;  // valor para CO2 - 4mA
float maxVoltsCO2  =  4720.0 ;  // valor para 100%       - 20mA

//============================================================================================================================================
float valminO2  =   0.00 ;
float valmaxO2  = 100.00 ;
float convO2    =   0.00 ;
float contaO2   =   0.00 ;
float indicaO2  =   0.00 ;


float valminCO  =   0.00 ;
float valmaxCO  = 100.00 ;
float convCO    =   0.00 ;
float contaCO   =   0.00 ;
float indicaCO  =   0.00 ;


float valminCO2  =   0.00 ;
float valmaxCO2  = 1000.00;
float convCO2    =   0.00 ;
float contaCO2   =   0.00 ;
float indicaCO2  =   0.00 ;


//============================================================================================================================================

float O2  =  0.0 ; //========== ta arredondando as casas 
float CO  =  0.00 ;
float CO2 =  0 ;

  
void u8g_prepare() // prepara o display ======================================================================================================
{
  u8g.setFont(u8g_font_ncenB12);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setColorIndex(1);
}


void u8g_Tela() // formata a Tela
{   

  
  u8g.drawRFrame(0,0,128,64,3); // moldura

  u8g.drawStr( 14, 17, "O   :             %")  ;
  u8g.drawStr( 9, 38 , "CO :           ppm" )  ;
  u8g.drawStr( 5, 59 , "CO  :           ppm" ) ;

 /*
  u8g.drawLine(0,21,128,21);
  u8g.drawLine(0,43,128,43); // linhas horizontais

  u8g.drawLine(43,0,43,64); // linhas verticais 
  u8g.drawLine(85,0,85,64);
  */
  


//=============== variavel O2 ================================================================================================================ 
  
  if (O2 >= 0 && O2 < 9.95) {
    u8g.setPrintPos(60,17);
    u8g.print(O2,1);
  } else {
    (O2 > 10 && O2 < 100); {
    u8g.setPrintPos(50,17);
    u8g.print(O2,1);
  }
 }

//=============== variavel CO ================================================================================================================
       
  if (CO >= 0 && CO < 9.95) {
    u8g.setPrintPos(60,38);
    u8g.print(CO,1);
 } else {
     (CO > 9.5 && CO < 100); {
    u8g.setPrintPos(50,38);
    u8g.print(CO,1);
 }
}

//=============== variavel CO2 ===============================================================================================================
      
  if (CO2 >= 0 && CO2 < 9.5) {
    u8g.setPrintPos(75,59);
    u8g.print(CO2,0);
} 
    
  if (CO2 > 9.5 && CO2 < 99.5) {
    u8g.setPrintPos(65,59);
    u8g.print(CO2,0);
} 
        
  if (CO2 > 99.5 && CO2 < 999.5) {
    u8g.setPrintPos(55,60);
    u8g.print(CO2,0);
}
 
   if  (CO2 >= 999.5 ){
    u8g.setPrintPos(45,60);
    u8g.print(CO2,0);
}  

//========== numeros pequenos ==========
    
  u8g.setFont(u8g_font_ncenB08);
  u8g.drawStr( 28, 18, "2");
  u8g.drawStr( 32, 60, "2");
}


void draw() // Rotina Desenho
{
  u8g_prepare();  
  u8g_Tela();  
} 


void setup() 
{
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

  O2 = contaO2   ;
  CO = contaCO   ;
  CO2 = contaCO2 ;
  
  
//========== limite das variaveis ============================================================================================================
  
  if (O2 > 30.0) {
    O2 = 30.0;
  }

  if (CO > 20) {
    CO = 20;
  }

  if (CO2 > 1000) {
    CO2 = 1000;
  }


  //========== limite dos negativos das variaveis ==============================================================================================
 
  if (O2 < 0) {
    O2 = 0;
  }

  if (CO < 0) {
    CO = 0;
  }

  if (CO2 < 0) {
    CO2 = 0;
  }

  //========== O2 contas =======================================================================================================================
  
  adc0.setMultiplexer(ADS1115_MUX_P0_NG);
  adc0.getConversion();
  adc0.setRate(ADS1115_RATE_8);
  convO2 = adc0.getMilliVolts();
  
  contaO2 = ((( convO2 - zeroVoltsO2 ) * ( valmaxO2 - valminO2 )) / ( maxVoltsO2 - zeroVoltsO2 )) + valminO2 ;
 
  if (contaO2 <= 0.0)
    indicaO2 = 0.0;
    else if (contaO2 >= 99.9)
    indicaO2 = 99.9;
          else
    indicaO2 = contaO2;

//========== CO contas ==========
  adc0.setMultiplexer(ADS1115_MUX_P0_NG);
  adc0.getConversion();
  adc0.setRate(ADS1115_RATE_8);
  convCO = adc0.getMilliVolts();

  contaCO = ((( convCO - zeroVoltsCO ) * ( valmaxCO - valminCO )) / ( maxVoltsCO - zeroVoltsCO )) + valminCO ;
 
  if (contaCO <= 0.0)
    indicaCO = 0.0;
    else if (contaCO >= 99.9)
    indicaCO = 99.9;
          else
    indicaCO = contaCO;

//========== CO2 contas ==========
  adc0.setMultiplexer(ADS1115_MUX_P0_NG);
  adc0.getConversion();
  adc0.setRate(ADS1115_RATE_8);
  convCO2 = adc0.getMilliVolts();


  contaCO2 = ((( convCO2 - zeroVoltsCO2 ) * ( valmaxCO2 - valminCO2 )) / ( maxVoltsCO2 - zeroVoltsCO2 )) + valminCO2 ;
 
  if (contaCO2 <= 0.0)
    indicaCO2 = 0.0;
    else if (contaCO2 >= 99.9)
    indicaCO2 = 99.9;
          else
    indicaCO2 = contaCO2;

//========== X contas ==========


    
  Serial.print("Valor O2 = ")  ; Serial.println(convO2,6)  ;
  Serial.print("conta O2 = ")  ; Serial.println(contaO2) ;
  Serial.print("Indica O2 = ") ; Serial.println(indicaO2);
  Serial.println();
  Serial.println();
  
  Serial.print("Valor CO = ")  ; Serial.println(convCO,6)  ;
  Serial.print("conta CO = ")  ; Serial.println(contaCO) ;
  Serial.print("Indica CO = ") ; Serial.println(indicaCO);
  Serial.println();
  Serial.println();
  
  Serial.print("Valor CO2 = ")  ; Serial.println(convCO2,6)  ;
  Serial.print("conta CO2 = ")  ; Serial.println(contaCO2) ;
  Serial.print("Indica CO2 = ") ; Serial.println(indicaCO2);
  Serial.println();
  Serial.println();

  
  delay (500);
}
