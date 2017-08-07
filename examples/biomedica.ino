#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include "taurus.h"
#include <ESP8266WiFi.h>

#define sensorPin  A0
#define BOTtoken "BOTTOKEN"
#define BOT_SCAN_MESSAGE_INTERVAL 1000

taurus taurus("SERIAL");
WiFiClientSecure client1;
UniversalTelegramBot bot(BOTtoken, client1);

uint8_t sensorValue = 0;
long lastTimeScan;

void setup() {
  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  digitalWrite(BUILTIN_LED, HIGH);
  WiFi.begin("SSID", "PASSWORD");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop()
{
  sensorValue = analogRead(sensorPin);
  taurus.write_sensor("SENSORID", sensorValue);
  delay(500);

  if (millis() > lastTimeScan + BOT_SCAN_MESSAGE_INTERVAL)  
  {
    // Serial.print("Checking messages - ");
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    // Serial.println(numNewMessages);
    while (numNewMessages) {
      // Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeScan = millis();
  }
}


// Trata as novas mensagens que chegaram
void handleNewMessages(int numNewMessages)
{
  // Serial.println("handleNewMessages");
  // Serial.println(String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    // Pessoa que está enviando a mensagem
    String from_name = bot.messages[i].from_name;
    if (from_name == "") from_name = "Convidado";

    // Tratamento para cada tipo de comando a seguir.
    if ( text == "/getsensor") {
      String message = "O valor do sensor é de " + String(sensorValue, DEC) + ".\n";
      bot.sendMessage(chat_id, message, "Markdown");
    }


    // Comando de inicio de conversa no telegram
    if (text == "/start") {
      String welcome = from_name + ", bem vindo ao Bot da Casa Viebrantz.\n";
      welcome += "Para interagir com a casa, use um dos comandos a seguir.\n\n";
      welcome += "/ledon : para ligar o Led \n";
      welcome += "/ledoff : para desligar o Led \n";
      welcome += "/relayon : para ligar o Relê \n";
      welcome += "/relayoff : para desligar o Relê \n";
      welcome += "/env : saber a temperatura e umidade do ambiente \n";
      welcome += "/status : para saber o status dos sensores e atuadores \n";
      bot.sendMessage(chat_id, welcome, "Markdown");
    }

    if (text == "/ledon") {
      digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)
      bot.sendMessage(chat_id, "Led está ligado", "");
    }

    if (text == "/ledoff") {
      digitalWrite(LED_BUILTIN, HIGH);    // turn the LED off (LOW is the voltage level)
      bot.sendMessage(chat_id, "Led está desligado", "");
    }
  }
}
