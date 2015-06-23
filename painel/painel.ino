/*
Dispositivo para painel em que o som aumento 
segundo a aproximação do visitante.
Criado para a Exposição "Discoteca 80: um projeto modernista".
Licença: GNU. 
*/

#include <Wtv020sd16p.h> //carrega a biblioteca do som

int resetPin = 2;  // The pin number of the reset pin.
int clockPin = 3;  // The pin number of the clock pin.
int dataPin = 4;  // The pin number of the data pin.
int busyPin = 5;  // The pin number of the busy pin.

/*
Create an instance of the Wtv020sd16p class.
 1st parameter: Reset pin number.
 2nd parameter: Clock pin number.
 3rd parameter: Data pin number.
 4th parameter: Busy pin number.
 */
Wtv020sd16p wtv020sd16p(resetPin,clockPin,dataPin,busyPin);

//define as constantes e os pinos
const int trigPin = 12;
const int echoPin = 13;
int volume = 0;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //Inicializa o módulo MP3.
  wtv020sd16p.reset();

}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long duracao = pulseIn(echoPin, HIGH);
  int distancia = duracao / 58;
  
  //Plays synchronously an audio file 0. Busy pin is used for this method.
  wtv020sd16p.playVoice(0);
  
  //Plays asynchronously an audio file 1.
  wtv020sd16p.asyncPlayVoice(1);
  
  //Plays audio file for 5 seconds.
  delay(5000);
  
  //Switch to file number 2.
  wtv020sd16p.asyncPlayVoice(2);
  
  //Plays it for 5 seconda.
  delay(5000);
  
  //Switch back to file number 1.
  wtv020sd16p.asyncPlayVoice(1);
  
  //Pauses audio for 5 seconds.  
  wtv020sd16p.pauseVoice();
  delay(5000);
  
  //Resumes audio and play for next 5 seconds.
  wtv020sd16p.pauseVoice();
  delay(5000);  
  
  //Stops current audio file playing.
  wtv020sd16p.stopVoice();

  //Plays synchronously an audio file. Busy pin is used for this method.  
  wtv020sd16p.asyncPlayVoice(2);
  delay(2000);   

  
  if(distancia > 100){
    volume = 0;
  }else if(distancia >= 75 && distancia <= 100){
    volume = 2;      
  }

  //Change the volume to 50%.
  wtv020sd16p.setVolume(4);
  delay(2000);   

  //Mutes audio file number 2 during 2 seconds.
  wtv020sd16p.mute();
  delay(2000);
  
  //Unmutes audio file number 2 during 2 seconds.
  wtv020sd16p.unmute();
  delay(2000);    
  
  //Stops current audio file playing.
  wtv020sd16p.stopVoice();
}



