//リレーに直接、繋がらない方

#include<WiFi.h>
const char *ssid="ESP32-WiFi"; //サーバーのSSID
const char *pass="esp32wifi"; //サーバーのパスワード
static WiFiClient client; //WiFiClient型でclientと宣言
const int EMS=23;
 
int buttonState=0;

void setup() {
  pinMode(EMS, INPUT_PULLDOWN);
  
  Serial.begin(115200);
  WiFi.begin(ssid,pass);  //サーバーに接続
  Serial.printf("\n");
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.printf("\n");
  Serial.println("WiFi Connected");
  IPAddress ip(192,168,0,9);  //サーバーのIPアドレス
  client.connect(ip,80);  //IPアドレスとポート番号を指定して接続
}
//単純に一文字送っています
char value;
void loop()
{
      while(client.connected()){
        delay(0.1);
      buttonState = digitalRead(EMS);
        if (buttonState == LOW) {
        Serial.println("押してる    ");
        client.write('1');
        
      } else {
        Serial.println("押せ       ");
        client.write('0');
        
      }
      //delay(0.1);
    }
  
}
