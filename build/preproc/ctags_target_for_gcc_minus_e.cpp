# 1 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino"
# 2 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino" 2
# 3 "c:\\Users\\iclee\\Programming\\Arduino\\lightSwitch\\lightswitcher.ino" 2

int buttonPin = 2;
int servoPin = 3;
int recvPin = 4;

Servo servo;
IRrecv irrecv(recvPin);
decode_results results;

int initialAngle = 30;
int lightOffAngle = 0;
int lightOnAngle = 60;

bool isLightOn = false;

void setup() {
    Serial.begin(9600);

    pinMode(buttonPin, 0x0);
    servo.attach(servoPin);
    servo.write(initialAngle);

    irrecv.enableIRIn();
}

void loop() {
    if (irrecv.decode(&results)) {
        Serial.println(results.value, 16);

        if (results.value == 0xFF6897) {
            isLightOn = !isLightOn;
            servo.write(lightOffAngle);
        } else if (results.value == 0xFF30CF) {
            isLightOn = !isLightOn;
            servo.write(lightOnAngle);
        }

        delay(250);
        irrecv.resume();
    }

    if (digitalRead(buttonPin) == 1) {
        isLightOn = !isLightOn;
        if (isLightOn) {
            servo.write(lightOnAngle);
        } else {
            servo.write(lightOffAngle);
        }
        delay(250);
    }
}
