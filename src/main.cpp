#include <Arduino.h>
#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino


#include <NeoPixelBus.h>

const uint16_t PixelCount = 4; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 26;  // make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 128

NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

int state = 0;
bool stateChanged = false;

int brightness = 0;

int saturation[4] = {0, 0, 0, 0};

int colors[4] = {0, 0, 0, 0};

int stepSize = 0;

long now = 0;
long last = 0;

BluetoothSerial ESP_BT; //Object for Bluetooth

void setup()
{
    Serial.begin(115200);
    while (!Serial); // wait for serial attach

    ESP_BT.begin("Tobis_riesen_pimmel"); //Name of your Bluetooth Signal

    Serial.println();
    Serial.println("Initializing...");
    Serial.flush();

    // this resets all the neopixels to an off state
    strip.Begin();
    strip.Show();


    Serial.println();
    Serial.println("Running...");
}


void loop()
{
  now = millis();

  if (ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    String key = (String)ESP_BT.readStringUntil('#'); //Read what we recevive until #
    String value = (String)ESP_BT.readStringUntil('\n'); //Read what we recevive until /n
    Serial.print("Received: "); Serial.println(key + ": " + value);
    if(key.equals("state")) 
    {
      stateChanged = true;
      state = value.toInt();
    }
    // TODO handle all available arguments
    // color4#145
    // if (key.startsWith("color")){colors[key.charAt(5).toInt()]}
  }

  // init state
  if (stateChanged)
  {
    switch(state)
    {
      // TODO add case for every state
      case 0:
        strip.ClearTo(HsbColor(0.0, 0.0, 0.0));
        break;

      case 1:
        strip.ClearTo(HsbColor(((float)colors[0]/255),((float)saturation[0]/255),((float)brightness/255)));
        break;

      case 2:
      strip.ClearTo(HsbColor(0.0, 1.0, 0.5));
      break;

    }
  }
if (now - last >= stepSize)
  {
    //do an animation step
    switch(state)
      {
        //TODO add case 0: for every animation state

        default:
          // do nothing
          break;
      }

    last = now;
  }
  strip.Show();
}
