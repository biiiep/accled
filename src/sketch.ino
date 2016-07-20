#include <Adafruit_ADXL345_U.h>
#include <Adafruit_Sensor.h>
#include <FastLED.h>
#include <Wire.h>

#include <stdlib.h>

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displayDataRate(void)
{
  Serial.print  ("Data Rate:    "); 
  
  switch(accel.getDataRate())
  {
    case ADXL345_DATARATE_3200_HZ:
      Serial.print  ("3200 "); 
      break;
    case ADXL345_DATARATE_1600_HZ:
      Serial.print  ("1600 "); 
      break;
    case ADXL345_DATARATE_800_HZ:
      Serial.print  ("800 "); 
      break;
    case ADXL345_DATARATE_400_HZ:
      Serial.print  ("400 "); 
      break;
    case ADXL345_DATARATE_200_HZ:
      Serial.print  ("200 "); 
      break;
    case ADXL345_DATARATE_100_HZ:
      Serial.print  ("100 "); 
      break;
    case ADXL345_DATARATE_50_HZ:
      Serial.print  ("50 "); 
      break;
    case ADXL345_DATARATE_25_HZ:
      Serial.print  ("25 "); 
      break;
    case ADXL345_DATARATE_12_5_HZ:
      Serial.print  ("12.5 "); 
      break;
    case ADXL345_DATARATE_6_25HZ:
      Serial.print  ("6.25 "); 
      break;
    case ADXL345_DATARATE_3_13_HZ:
      Serial.print  ("3.13 "); 
      break;
    case ADXL345_DATARATE_1_56_HZ:
      Serial.print  ("1.56 "); 
      break;
    case ADXL345_DATARATE_0_78_HZ:
      Serial.print  ("0.78 "); 
      break;
    case ADXL345_DATARATE_0_39_HZ:
      Serial.print  ("0.39 "); 
      break;
    case ADXL345_DATARATE_0_20_HZ:
      Serial.print  ("0.20 "); 
      break;
    case ADXL345_DATARATE_0_10_HZ:
      Serial.print  ("0.10 "); 
      break;
    default:
      Serial.print  ("???? "); 
      break;
  }  
  Serial.println(" Hz");  
}

void displayRange(void)
{
  Serial.print  ("Range:         +/- "); 
  
  switch(accel.getRange())
  {
    case ADXL345_RANGE_16_G:
      Serial.print  ("16 "); 
      break;
    case ADXL345_RANGE_8_G:
      Serial.print  ("8 "); 
      break;
    case ADXL345_RANGE_4_G:
      Serial.print  ("4 "); 
      break;
    case ADXL345_RANGE_2_G:
      Serial.print  ("2 "); 
      break;
    default:
      Serial.print  ("?? "); 
      break;
  }  
  Serial.println(" g");  
}



#define LED_PIN     5
#define COLOR_ORDER GRB
#define CHIPSET     NEOPIXEL
#define NUM_LEDS    3

#define BRIGHTNESS  5
#define FRAMES_PER_SECOND 20

CRGB leds[NUM_LEDS];

void setup() {
  delay(200); // sanity delay
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);

#ifndef ESP8266
  while (!Serial); // for Leonardo/Micro/Zero
#endif
  Serial.begin(115200);
  Serial.println("Accelerometer Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);
  // displaySetRange(ADXL345_RANGE_8_G);
  // displaySetRange(ADXL345_RANGE_4_G);
  // displaySetRange(ADXL345_RANGE_2_G);
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
  
  /* Display additional settings (outside the scope of sensor_t) */
  displayDataRate();
  displayRange();
  Serial.println("");
}

void loop()
{
  // Add entropy to random number generator; we use a lot of it.
  //random16_add_entropy( random());

  /* Get a new sensor event */ 
  sensors_event_t event; 
  accel.getEvent(&event);

#if 0
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
#endif

  MyFunc(event); // run simulation frame

  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void MyFunc(sensors_event_t event)
{
	static uint8_t initial = 0;
	static int up = 1;
	int32_t r, g, b;

	for (int i; i < NUM_LEDS; i++) {
		//fill_rainbow(&leds[i], 1, initial + i * 20, 5);
		r = 0; g = 0; b = 0;

#if 0
#define MY_CONSTANT 4
		r = event.acceleration.x * MY_CONSTANT;
		g = (int32_t)(event.acceleration.y * MY_CONSTANT) << 8;
		b = (int32_t)(event.acceleration.z * MY_CONSTANT) << 16;
#else
#if 0
#define MY_CONSTANT 256
		r = (uint8_t)((abs(event.acceleration.x + 10) * MY_CONSTANT) / MY_CONSTANT);
		g = (uint8_t)((abs(event.acceleration.y + 10) * MY_CONSTANT) / MY_CONSTANT);
		b = (uint8_t)((abs(event.acceleration.z + 10) * MY_CONSTANT) / MY_CONSTANT);
#else
#define MY_CONSTANT 2
		int32_t intensity = (uint8_t)abs(event.acceleration.y) / 2;
		intensity = intensity == 0 ? 1 : intensity;

		b = (uint8_t)((abs(event.acceleration.x + 10) * MY_CONSTANT));
		g = 0; //(uint8_t)((abs(event.acceleration.y + 10) * MY_CONSTANT));
		r = (uint8_t)((abs(event.acceleration.z + 10) * MY_CONSTANT));

		b *= intensity;
		r *= intensity;

		if (i == 1) {
			if (r < 15)
				r = 0;
			if (b < 15)
				b = 0;
		} else if (i == 2) {
			if (r < 30)
				r = 0;
			if (b < 30)
				b = 0;
		}


#endif

		b <<= 0; 
		g <<= 8;
		r <<= 16;
#endif
#if 1
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print("r: "); Serial.print(r >> 16); Serial.print("  ");
  Serial.print("g: "); Serial.print(g >> 8); Serial.print("  ");
  Serial.print("b: "); Serial.print(b >> 0); Serial.print("  ");Serial.println("m/s^2 ");
#endif

		leds[i] = r | g | b;
	}
	if (initial == 30)
		up = 0;
	if (initial == 0)
		up = 1;

	if (up)
		initial++;
	else
		initial--;
}
