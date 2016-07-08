#include <FastLED.h>

#define LED_PIN     5
#define COLOR_ORDER GRB
#define CHIPSET     NEOPIXEL
#define NUM_LEDS    8

#define BRIGHTNESS  5
#define FRAMES_PER_SECOND 20

CRGB leds[NUM_LEDS];

void setup() {
  delay(1000); // sanity delay
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, NUM_LEDS);
}

void loop()
{
  // Add entropy to random number generator; we use a lot of it.
  //random16_add_entropy( random());

  MyFunc(); // run simulation frame

  FastLED.show(); // display this frame
  FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void MyFunc()
{
#if 0
	static uint8_t initial = 0;

	for (int i; i < NUM_LEDS; i++) {
		//fill_rainbow(&leds[i], 1, initial + i * 20, 5);
		leds[i] = initial << i;

	}
#else
	static uint8_t initial = 0;
	static int up = 1;
	int32_t r, g, b;

	for (int i; i < NUM_LEDS; i++) {
		//fill_rainbow(&leds[i], 1, initial + i * 20, 5);
		r = 0; g = 0; b = 0;

		int32_t val = initial;

		if (i & 1)
			r = val;
		else if (i & 2)
			g = val << 8;
		else if (i & 4)
			b = val << 16;

		leds[i] = r | g | b;
	}
	if (initial == 30)
		up = 0;
	if (initial == 0)
		up = 1;
#endif

	if (up)
		initial++;
	else
		initial--;
}
