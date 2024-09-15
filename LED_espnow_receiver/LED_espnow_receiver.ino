#include <esp_now.h>
#include <WiFi.h>


typedef struct struct_message {
  int potValue;
} struct_message;


const int ledPin_white = 17; 
const int ledPin_green = 16;
const int ledPin_blue = 4;


void OnDataRecv(const esp_now_recv_info* info, const uint8_t* incomingData, int len) {
  struct_message* data = (struct_message*)incomingData;

  int potValue = data->potValue;

if(potValue<=1024){
    digitalWrite(ledPin_white, LOW);
    digitalWrite(ledPin_green, LOW);
    digitalWrite(ledPin_blue, LOW);
  }
  else if(potValue<=2048){
   digitalWrite(ledPin_white, HIGH);
    digitalWrite(ledPin_green, LOW);
    digitalWrite(ledPin_blue, LOW);
  }
  else if(potValue<=3072){
   digitalWrite(ledPin_white, HIGH);
    digitalWrite(ledPin_green, HIGH);
    digitalWrite(ledPin_blue, LOW);
  }
  else{
   digitalWrite(ledPin_white, HIGH);
    digitalWrite(ledPin_green, HIGH);
    digitalWrite(ledPin_blue, HIGH);
  }
  

  Serial.print("Alınan Potansiyometre Değeri: ");
  Serial.println(potValue);
}

void setup() {
  Serial.begin(115200);

  
  pinMode(ledPin_white, OUTPUT);
   pinMode(ledPin_green, OUTPUT);
    pinMode(ledPin_blue, OUTPUT);

  WiFi.mode(WIFI_STA);


  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW başlatılamadı");
    return;
  }

  
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  
  delay(1000);
}
