/* TOM'S Hobby & サインカフェベリーユー  */
/* 8月29日(木) 20:58                    */
/* server側                            */

//リレーに直接繋がる方

#include<WiFi.h>
#include <Wire.h>
#include "SSD1306.h"
const char *ssid="ESP32-WiFi"; //SSID
const char *pass="esp32wifi"; //パスワード
const IPAddress ip(192,168,0,9);  //サーバーのIPアドレス
const IPAddress subnet(255,255,255,0);  //サブネットマスク

const int relay=19;
int buttonState=0;
SSD1306  display(0x3c, 21, 22); //SSD1306インスタンスの作成（I2Cアドレス,SDA,SCL）

WiFiServer server(80);
void setup()
{
  pinMode(relay, OUTPUT);
  display.init();    //ディスプレイを初期化
  display.setFont(ArialMT_Plain_16);    //フォントを設定
  Serial.begin(115200);
  WiFi.softAP(ssid,pass);  //SSIDとパスの設定
  delay(100); //接続失敗防止
  WiFi.softAPConfig(ip,ip,subnet);  //IPアドレス、ゲートウェイ、サブネットマスクの設定
  IPAddress myIP = WiFi.softAPIP(); //WiFi.softAPIP()でWiFi起動
  server.begin(); //サーバーを起動(htmlを表示させるため)
  Serial.println();
  /*各種情報を表示*/
  Serial.println("WiFi connected");
  Serial.print("SSID：");
  Serial.println(ssid);
  Serial.print("AP IP address：");
  Serial.println(myIP);
  Serial.println("Server start!");
}

char value;   //この　型をいろいろ試すと面白いです
void loop()
{
  display.drawLine(30, 0, 90,60);
  display.drawLine(90, 0, 30,60);
  display.display();
  //接続したクライアントの情報を得る。
  WiFiClient client = server.available();
  if(client){
    Serial.println("new client");
    while(client.connected()==true){
    
    value=client.read();
    
    if(value=='1'){
      digitalWrite(relay, LOW);
      display.drawLine(30, 0, 90,60);
      display.drawLine(90, 0, 30,60);
      display.drawCircle(60, 30, 30);
      
     }else if(value=='0'){
      digitalWrite(relay, HIGH);
      display.clear();
      display.drawCircle(60, 30, 30);
     }
     
   Serial.println(value);
   //押してるとき1が出力される
   //押してないとき0が出力される
   
   display.display();   //指定された情報を描画
   //delay(0.1);
   
  }
  }else{
  
  digitalWrite(relay, LOW); 
  }
  
  
}
