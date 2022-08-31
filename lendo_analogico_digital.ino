#include <U8glib.h>
U8GLIB_ST7920_128X64_1X u8g(4, 5, 6, 7); //Enable, RW, RS, RESET


#include <Adafruit_ADS1X15.h>
#include <Wire.h>

float mV = 0.00;
 
Adafruit_ADS1115 ads;
const float multiplier = 0.1875F;

void u8g_prepare() // prepara o display =======================================================================================================
{
  u8g.setFont(u8g_font_7x13B);
  u8g.setFontRefHeightExtendedText();
  u8g.setDefaultForegroundColor();
  u8g.setColorIndex(1);
  
}


void u8g_Tela(){
  u8g.setPrintPos(5,15);
  u8g.print("Tensao:");
  u8g.setPrintPos(5,30);
  u8g.print("mV:");
  u8g.setPrintPos(25,30);
  u8g.print(mV);
  u8g.setPrintPos(60,30);
  u8g.print("%");
}

      
void setup () {
 Serial.begin(9600);
 ads.begin();
}

void draw() // Rotina Desenho
{
  u8g_prepare();  
  u8g_Tela();  
} 


void loop() {
  
      u8g.firstPage();
      do 
    {
      draw ();
    }
      while( u8g.nextPage());

     
  
 int16_t adc0;
 adc0 = ads.readADC_SingleEnded(0);
 Serial.print("AIN0: "); Serial.println(adc0 * multiplier);
 Serial.println(mV);
 mV = ((adc0 * multiplier) / 5000) * 100;

 Serial.println();
 delay(1000);

}
