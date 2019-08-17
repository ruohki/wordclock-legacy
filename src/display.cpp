#include "display.h"

Display::Display() {
  FastLED.addLeds<WS2812B, PIN, RGB>(currentLeds, NUMPIXELS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);
  FastLED.clear();
};

Display::~Display() {
  FastLED.clear();
}


void Display::setDefault() {
  for (auto i = 0; i < NUMPIXELS; i++) {
    targetLeds[i] = CRGB::Black;
  }

  for (int i = 0; i < size(DEFAULT_LIT_PIXEL); i++) {
    uint8_t b = pgm_read_byte(DEFAULT_LIT_PIXEL + i);
    targetLeds[b] = defaultColor;
  }
}

void Display::setMinute(uint8_t minute) {
  for (int i = 0; i < 4; i++) {
    uint8_t b = (NUMPIXELS - 4) + i;
    targetLeds[b] = (minute % 5) > i ? defaultColor : offColor;
  }

  if (minute >= 5 && minute < 10) {
    printArray(MFUENF, size(MFUENF));
    printArray(NACH, size(NACH));
  } else if (minute >= 10 && minute < 15) {
    printArray(MZEHN, size(MZEHN));
    printArray(NACH, size(NACH));
  } else if (minute >= 15 && minute < 20) {
    printArray(VIERTEL, size(VIERTEL));
  } else if (minute >= 20 && minute < 25) {
    printArray(ZWANZIG, size(ZWANZIG));
    printArray(NACH, size(NACH));
  } else if (minute >= 25 && minute < 30) {
    printArray(MFUENF, size(MFUENF));
    printArray(VOR, size(VOR));
    printArray(HALB, size(HALB));
  } else if (minute >= 30 && minute < 35) {
    printArray(HALB, size(HALB));
  } else if (minute >= 35 && minute < 40) {
    printArray(MFUENF, size(MFUENF));
    printArray(NACH, size(NACH));
    printArray(HALB, size(HALB));
  } else if (minute >= 40 && minute < 45) {
    printArray(MZEHN, size(MZEHN));
    printArray(NACH, size(NACH));
    printArray(HALB, size(HALB));
  } else if (minute >= 45 && minute < 50) {
    printArray(DREIVIERTEL, size(DREIVIERTEL));
  } else if (minute >= 50 && minute < 55) {
    printArray(MZEHN, size(MZEHN));
    printArray(VOR, size(VOR));
  } else if (minute >= 55 && minute < 60) {
    printArray(MFUENF, size(MFUENF));
    printArray(VOR, size(VOR));
  }

  if (minute < 5) {
    printArray(UHR, size(UHR));
  }
}

void Display::printArray(const uint8_t * arr, int n) {
  for (auto i = 0; i < n; i++) {
    uint8_t b = pgm_read_byte(arr + i);
    targetLeds[b] = defaultColor;
  }
}


void Display::instantCommitChanges() {
  for (int i = 0; i < NUMPIXELS; i++) {
    currentLeds[i] = targetLeds[i];
  }
  FastLED.show();
}

void Display::render(uint8_t speed) {
  for (int i = 0; i < NUMPIXELS; i++) {
    currentLeds[i] = blend(currentLeds[i], targetLeds[i], speed);
  }
  FastLED.show();
}

void Display::setTime(uint8_t hour, uint8_t minute) {
  setDefault();
  setMinute(minute);

  if (hour >= 12) {
    hour -= 12;
  }

  if (!(minute >= 15 && minute < 20) && !(minute >= 25 && minute < 50)) {

//  if ((minute < 15 || !(minute > 45 && minute < 50) || !(minute >= 50 && minute < 60))) {
    switch(hour) {
      case 1:
        if (minute >= 5) {
          printArray(EINS, size(EINS));
        } else {
          printArray(EIN, size(EIN));
        }
        break;
      case 2:
        printArray(ZWEI, size(ZWEI));
        break;
      case 3:
        printArray(DREI, size(DREI));
        break;
      case 4:
        printArray(VIER, size(VIER));
        break;
      case 5:
        printArray(FUENF, size(FUENF));
        break;
      case 6:
        printArray(SECHS, size(SECHS));
        break;
      case 7:
        printArray(SIEBEN, size(SIEBEN));
        break;
      case 8:
        printArray(ACHT, size(ACHT));
        break;
      case 9:
        printArray(NEUN, size(NEUN));
        break;
      case 10:
        printArray(ZEHN, size(ZEHN));
        break;
      case 11:
        printArray(ELF, size(ELF));
        break;
      case 0:
        printArray(ZWOELF, size(ZWOELF));
        break;
    }
  } else {

    switch(hour) {
      case 1:
        printArray(ZWEI, size(ZWEI));
        break;
      case 2:
        printArray(DREI, size(DREI));
        break;
      case 3:
        printArray(VIER, size(VIER));
        break;
      case 4:
        printArray(FUENF, size(FUENF));
        break;
      case 5:
        printArray(SECHS, size(SECHS));
        break;
      case 6:
        printArray(SIEBEN, size(SIEBEN));
        break;
      case 7:
        printArray(ACHT, size(ACHT));
        break;
      case 8:
        printArray(NEUN, size(NEUN));
        break;
      case 9:
        printArray(ZEHN, size(ZEHN));
        break;
      case 10:
        printArray(ELF, size(ELF));
        break;
      case 11:
        printArray(ZWOELF, size(ZWOELF));
        break;
      case 0:
        if (minute >= 5) {
          printArray(EINS, size(EINS));
        } else {
          printArray(EIN, size(EIN));
        }
        break;
    }
  }
}