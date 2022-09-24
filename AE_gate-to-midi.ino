#include <MIDI.h>

//struct HairlessMidiSettings : public midi::DefaultSettings
//{
//   static const bool UseRunningStatus = false;
//   static const long BaudRate = 115200;
//};
//MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, HairlessMidiSettings);
//MIDI_CREATE_DEFAULT_INSTANCE();

struct CustomBaudRate : public midi::DefaultSettings{
  static const long BaudRate = 115200;
};
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, CustomBaudRate);


bool trig[8];
bool mem[8];
unsigned long thistime[8];
unsigned long inittime = millis();
unsigned long lasttime[8] = {inittime, inittime, inittime, inittime, inittime, inittime, inittime, inittime};
unsigned long timediff;
int note=1;
int x;
int led=13;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);

  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(115200);

  MIDI.setHandleControlChange(handleControlChange);

  for (x=0;x<8;x++){
    trig[x]=LOW;
    mem[x]=LOW;
  }

  delay(1000);
}

// control change
void handleControlChange(byte channel, byte num, byte val)
{
   if (num == 3) {
    MIDI.sendControlChange(127,3,1); // if receive cc 3, respond with handshake cc. In this case, cc#127, value 1 for this firmware, channel 1
   }
}

void loop() {
  MIDI.read();
  // put your main code here, to run repeatedly:
  trig[0] = digitalRead(2); // note 1, pin 2
  trig[1] = digitalRead(3); // note 2, pin 3
  trig[2] = digitalRead(4);
  trig[3] = digitalRead(5);
  trig[4] = digitalRead(6);
  trig[5] = digitalRead(7); // note 3
  trig[6] = digitalRead(8); // note 4
  trig[7] = digitalRead(9); // note 

  for (x=0;x<8;x++){
    if (trig[x]==HIGH){
      if (mem[x]==LOW){
        note = x + 1;
        thistime[x] = millis();
        timediff = thistime[x] - lasttime[x];
        if (timediff > 150) {
          MIDI.sendNoteOn(note, 127, 1); //send note on to notes 1 to 4
        };
        lasttime[x] = thistime[x];
        mem[x]=HIGH;
        digitalWrite(led, HIGH);
    }}
  if (trig[x]==LOW){
    if (mem[x]==HIGH){
      note = x + 1;
      MIDI.sendNoteOff(note, 0, 1); //send note off
      mem[x]=LOW;
      digitalWrite(led, LOW);
  }}}

}
