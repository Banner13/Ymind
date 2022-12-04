#include <Wire.h>
#define SDA_PIN 4
#define SLK_PIN 5


uint8_t address;
float T; 

float RH;

void setup()
{
    uint8_t error, data;
    Wire.begin(SDA_PIN,SLK_PIN);

    delay(500);

    address = 0x38;

    Serial.begin(115200);
    while (!Serial);             // Leonardo: wait for serial monitor
    Serial.println("I2C Scanner");

    Wire.beginTransmission(address);
    error = Wire.endTransmission();


}

void init_aht10()
{
    uint8_t error;
    Wire.beginTransmission(address);
    Wire.write(0xE1);
    Wire.write(0x08);
    Wire.write(0x00);
    error = Wire.endTransmission();
    delay(100);
    printf("init error = %d\n", error);
}

void test()
{
    int data[6];
    uint8_t error;
    Wire.beginTransmission(address);
    Wire.write(0xAC);
    Wire.write(0x33);
    Wire.write(0x00);

    error = Wire.endTransmission();

    delay(80);

    Wire.requestFrom(address, 6);

    for (int i = 0; i < 6; i++)
    {
        data[i] = Wire.read();
    }
    RH = ((data[1] << 12) | (data[2] << 4)) | (data[3] >> 4);
    T = ((data[3] & 0x0f) << 16) | (data[4] << 8) | data[5];
    RH = (RH / pow(2, 20)) * 100;
    T = (T / pow(2, 20)) * 200 - 50;
    Serial.print("RH = ");
    Serial.println(RH);
    Serial.print("T = ");
    Serial.println(T);

    printf("error = %d\r\n", error);
}

void loop()
{
        test();
    delay(5000);           // wait 5 seconds for next scan
} 