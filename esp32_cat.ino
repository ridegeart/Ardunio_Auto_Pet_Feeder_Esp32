#include "initPins.h"     // 腳位與系統模組
#include "LineLib.h"     // Line Notify自訂模組
#include "DS1302.h"  // 時間專用模組
#include <Servo.h>   //伺服馬達
#include "toneMelody.h"

Servo myservo;
int servoPin = 16;
int pos = 0;    // 定義舵機轉動位置

bool food = false;
int PIRSensor = 13; 
int sensorValue = 0;  
int ledPin = 15; 

void setup()
{
    initALL() ; //系統硬體/軟體初始化
    initWiFi() ;  //網路連線，連上熱點
    ShowInternet();  //秀出網路連線資訊
    initLine() ;    //起始Line Notifier連線
    myservo.attach(servoPin);  // 設置舵機控制腳位
    pinMode(PIRSensor, INPUT);
    pinMode(ledPin, OUTPUT);
    delay(1000) ;
}

void loop()
{
    const char* dataTime = getDataTime() ;
    char Date[11],Time[6] ;
       
    for(int i = 0; i < 17; i++){
      if (i < 11){
        Date[i] = dataTime[i];
        }
      else{
        Time[i-11] = dataTime[i];
        }
      }
      
    Date[10] = '\0';
    Time[5] = '\0';
    
    Serial.println(Time);
    if(strcmp(Time, "19:47") == 0){
      //Line Message
      String msg ="目前date:"+String(Date)+", 目前time："+String(Time)+"已投餵睿睿";
      SendMsgtoLine(msg) ;
      food = true;
      //馬達
      for(pos = 0; pos <= 90; pos += 1) { 
         myservo.write(pos);
         delay(15); 
      } 
      // 180到0旋轉舵機，每次延時15毫秒 
      for(pos = 90; pos > 0; pos -= 1)
      {                               
        myservo.write(pos);
        delay(15);
      }
      //music
     //melodysetup();
    }
    
    if (food == true){
      sensorValue = digitalRead(PIRSensor);            //讀取 PIR Sensor 的狀態
      Serial.print("紅外線狀態：");
      Serial.println(sensorValue); //將訊號值印在序列埠螢幕上
      if (sensorValue == HIGH) {                       //如果訊號值是 HIGH，表示有感應到紅外線位移，有人，警報響起，LED 燈點亮               
        String msg ="目前date:"+String(Date)+", 目前time："+String(Time)+"睿睿進食中";
        SendMsgtoLine(msg) ;
        digitalWrite(ledPin, HIGH);
        food = false;
        delay(10000) ;
        digitalWrite(ledPin, LOW);
      } 
      else {                                           //如果訊號值是 LOW，沒人，則警報不響，LED 燈不亮  
        digitalWrite(ledPin, LOW);
      }
      }
      delay(30000) ;
}

/* Function to print the sending result via Serial */

void initALL()  //系統硬體軟體初始化
{
    Serial.begin(57600);
    Serial.println("System Start");
    initDS1302 ();
    //initMelody () ;
}
