#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;

const int buttonPin = 10; // The pin the button is connected to

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP); // Initialize the button pin as an input

  BLEDevice::init("G$ Test"); // Give your device a name
  pServer = BLEDevice::createServer(); // Create a BLE server
  BLEService* pService = pServer->createService(SERVICE_UUID); // Create a BLE service

  // Create a BLE characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY
                    );

  pCharacteristic->setValue("Waiting for button press..."); // Initial value
  pService->start(); // Start the service

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();  // Corrected to get the default advertising object
  pAdvertising->addServiceUUID(SERVICE_UUID);  // Ensure your device advertises its service
  pAdvertising->start();
  Serial.println("Waiting for a client connection to notify...");
}

void loop() {
  static unsigned long lastDebounceTime = 0; // the last time the output pin was toggled
  static bool lastButtonState = HIGH; // the previous reading from the input pin

  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button 
  // (i.e. the input went from HIGH to LOW), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > 50) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading == LOW) {
      String data = "Bluetooth Test 1,100.25,100,3,1234,150.5,150,6,4321";
      pCharacteristic->setValue(data.c_str());
      pCharacteristic->notify(); // Notify any connected clients
      Serial.println("Data sent over BLE: " + data);
      delay(200); // Simple debounce/handling delay
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
