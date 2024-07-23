# IOT_WeatherStation

This project demonstrates how to use an ESP8266 to interface with sensors and display data on an OLED screen. It reads temperature, humidity, and pressure from a BMP180 and DHT11 sensors, and sends the data to ThingSpeak for monitoring.

## Components

- **ESP8266**: Microcontroller with WiFi capability.
- **BMP180**: Barometric pressure sensor.
- **DHT11**: Temperature and humidity sensor.
- **OLED Display**: 128x32 pixel display.
- **ThingSpeak**: IoT platform for data visualization.

## Libraries Used

- `Adafruit_Sensor`
- `Adafruit_BMP085_U`
- `DHT`
- `Adafruit_GFX`
- `Adafruit_SSD1306`
- `ESP8266WiFi`
- `ThingSpeak`

## Installation

1. **Install Libraries**: Use the Arduino Library Manager to install the required libraries.
2. **Connect Components**: Follow the wiring instructions in the code comments.
3. **Configure WiFi**: Update `ssid` and `password` with your WiFi credentials.
4. **Configure ThingSpeak**: Replace `myChannelNumber` and `myWriteAPIKey` with your ThingSpeak channel details.

## Usage

1. **Upload Code**: Use the Arduino IDE to upload the code to your ESP8266.
2. **Monitor Output**: Check the OLED display for real-time sensor data.
3. **View Data**: Log in to ThingSpeak to view the uploaded sensor data.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
