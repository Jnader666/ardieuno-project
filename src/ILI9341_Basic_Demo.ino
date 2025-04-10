/*
 * ILI9341 Basic Demo
 * 
 * This sketch demonstrates basic functionality of the ILI9341 TFT display
 * using the Adafruit libraries.
 * 
 * Hardware Connections:
 * Arduino Pin | ILI9341 Pin
 * ---------------------
 * 5V          | VCC
 * GND         | GND
 * D10         | CS
 * D9          | DC
 * D13         | SCK
 * D11         | MOSI
 * D12         | MISO
 * D8          | RESET
 * 
 * Created: April 9, 2025
 * Author: Olson
 */

#include <SPI.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ILI9341.h> // Hardware-specific library

// Pin definitions
#define TFT_CS    10  // Chip select pin
#define TFT_DC     9  // Data/Command pin
#define TFT_MOSI  11  // Master Out Slave In pin
#define TFT_CLK   13  // Clock pin
#define TFT_RST    8  // Reset pin
#define TFT_MISO  12  // Master In Slave Out pin (optional, not used in this example)

// Create an instance of the display
// Using hardware SPI (faster):
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

// Alternatively, you can use software SPI (slower but more flexible with pin selection):
// Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST, TFT_MISO);

// Define some colors
#define BLACK    0x0000
#define BLUE     0x001F
#define RED      0xF800
#define GREEN    0x07E0
#define CYAN     0x07FF
#define MAGENTA  0xF81F
#define YELLOW   0xFFE0
#define WHITE    0xFFFF

void setup() {
  Serial.begin(9600);
  Serial.println("ILI9341 Test!"); 
  
  // Initialize the display
  tft.begin();
  
  // Read the display driver ID (should be 0x9341 for ILI9341)
  uint16_t identifier = tft.readID();
  Serial.print("Display Driver ID: 0x"); Serial.println(identifier, HEX); 
  
  // Set the rotation (0-3)
  // 0 = Portrait, 1 = Landscape, 2 = Portrait flipped, 3 = Landscape flipped
  tft.setRotation(1);
  
  // Fill the screen with a color
  tft.fillScreen(BLACK);
  
  // Display a welcome message
  displayWelcomeScreen();
  
  delay(2000);
  
  // Run the demo
  runDemo();
}

void loop() {
  // Nothing to do here, the demo runs once
}

void displayWelcomeScreen() {
  // Set text properties
  tft.setCursor(20, 30);
  tft.setTextColor(WHITE);
  tft.setTextSize(3);
  tft.println("ILI9341");
  
  tft.setCursor(20, 70);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Display Demo");
  
  tft.setCursor(20, 100);
  tft.setTextColor(CYAN);
  tft.setTextSize(1);
  tft.println("Arduino Project by Olson");
}

void runDemo() {
  // Clear the screen
  tft.fillScreen(BLACK);
  
  // Draw some shapes
  drawShapesDemo();
  delay(2000);
  
  // Draw some text
  tft.fillScreen(BLACK);
  drawTextDemo();
  delay(2000);
  
  // Draw color gradient
  tft.fillScreen(BLACK);
  drawColorGradient();
  delay(2000);
  
  // Run direct command demo
  directCommandDemo();
}

void drawShapesDemo() {
  // Draw a filled rectangle
  tft.fillRect(10, 10, 60, 40, RED);
  
  // Draw an outlined rectangle
  tft.drawRect(80, 10, 60, 40, GREEN);
  
  // Draw a filled circle
  tft.fillCircle(40, 90, 30, BLUE);
  
  // Draw an outlined circle
  tft.drawCircle(110, 90, 30, YELLOW);
  
  // Draw a filled triangle
  tft.fillTriangle(160, 10, 190, 50, 230, 10, MAGENTA);
  
  // Draw an outlined triangle
  tft.drawTriangle(160, 70, 190, 110, 230, 70, CYAN);
  
  // Draw some lines
  for (int i = 0; i < 20; i++) {
    tft.drawLine(250, 10, 310, 10 + i*5, WHITE);
  }
}

void drawTextDemo() {
  // Different text sizes
  tft.setCursor(10, 10);
  tft.setTextColor(WHITE);
  tft.setTextSize(1);
  tft.println("Size 1 Text"); 
  
  tft.setCursor(10, 30);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Size 2 Text"); 
  
  tft.setCursor(10, 60);
  tft.setTextColor(GREEN);
  tft.setTextSize(3);
  tft.println("Size 3"); 
  
  tft.setCursor(10, 100);
  tft.setTextColor(CYAN);
  tft.setTextSize(4);
  tft.println("Size 4"); 
  
  // Draw text with background
  tft.setCursor(200, 60);
  tft.setTextColor(MAGENTA, BLUE); // Text color, background color
  tft.setTextSize(2);
  tft.println("With BG"); 
}

void drawColorGradient() {
  int width = tft.width();
  int height = tft.height();
  
  // Draw a color gradient (rainbow effect)
  for (int y = 0; y < height; y++) {
    // Calculate a color based on the y position
    // This creates a smooth transition through the color spectrum
    int r, g, b;
    
    if (y < height/6) {
      // Red to Yellow
      r = 255;
      g = map(y, 0, height/6, 0, 255);
      b = 0;
    } else if (y < height*2/6) {
      // Yellow to Green
      r = map(y, height/6, height*2/6, 255, 0);
      g = 255;
      b = 0;
    } else if (y < height*3/6) {
      // Green to Cyan
      r = 0;
      g = 255;
      b = map(y, height*2/6, height*3/6, 0, 255);
    } else if (y < height*4/6) {
      // Cyan to Blue
      r = 0;
      g = map(y, height*3/6, height*4/6, 255, 0);
      b = 255;
    } else if (y < height*5/6) {
      // Blue to Magenta
      r = map(y, height*4/6, height*5/6, 0, 255);
      g = 0;
      b = 255;
    } else {
      // Magenta to Red
      r = 255;
      g = 0;
      b = map(y, height*5/6, height, 255, 0);
    }
    
    // Convert RGB to 565 color format
    uint16_t color = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    
    // Draw a horizontal line with this color
    tft.drawFastHLine(0, y, width, color);
  }
  
  // Add a label
  tft.setCursor(width/2 - 50, height/2 - 10);
  tft.setTextColor(BLACK);
  tft.setTextSize(2);
  tft.println("RAINBOW"); 
}

// Function to demonstrate direct command sending to the ILI9341
void directCommandDemo() {
  tft.fillScreen(BLACK);
  
  // Display title
  tft.setCursor(20, 10);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.println("Direct Command Demo"); 
  
  // Wait a moment
  delay(2000);
  
  // Demo 1: Display Inversion
  displayInversionDemo();
  delay(2000);
  
  // Demo 2: Scrolling
  scrollingDemo();
  delay(2000);
  
  // Demo 3: Display rotation using direct MADCTL command
  rotationDemo();
  delay(2000);
  
  // Demo 4: Partial display mode
  partialDisplayDemo();
  delay(2000);
  
  // Demo 5: Brightness control (if supported by display)
  brightnessDemo();
  delay(2000);
}

// Demo 1: Display Inversion
void displayInversionDemo() {
  tft.fillScreen(BLACK);
  
  // Draw some colored rectangles
  tft.fillRect(20, 20, 60, 60, RED);
  tft.fillRect(100, 20, 60, 60, GREEN);
  tft.fillRect(180, 20, 60, 60, BLUE);
  
  tft.setCursor(20, 100);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.println("Normal Colors"); 
  delay(1500);
  
  // Send INVON command (Display Inversion ON)
  tft.sendCommand(0x21); // INVON command
  
  tft.setCursor(20, 130);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.println("Inverted Colors"); 
  delay(1500);
  
  // Send INVOFF command (Display Inversion OFF)
  tft.sendCommand(0x20); // INVOFF command
  
  tft.setCursor(20, 160);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.println("Back to Normal"); 
}

// Demo 2: Scrolling
void scrollingDemo() {
  tft.fillScreen(BLACK);
  
  // Draw some content to scroll
  for (int i = 0; i < 10; i++) {
    tft.setCursor(20, 30 + i * 20);
    tft.setTextColor(random(0xFFFF)); // Random color
    tft.setTextSize(2);
    tft.print("Scroll Line "); 
    tft.println(i);
  }
  
  tft.setCursor(20, 240);
  tft.setTextColor(YELLOW);
  tft.setTextSize(2);
  tft.println("Scrolling Demo"); 
  
  delay(1000);
  
  // Define scroll area
  // Parameters: top_fixed_area, scrolling_area, bottom_fixed_area
  defineScrollArea(0, 240, 80);
  
  // Scroll the screen
  for (int i = 0; i < 240; i++) {
    scrollDisplay(i);
    delay(10);
  }
  
  // Scroll back
  for (int i = 240; i >= 0; i--) {
    scrollDisplay(i);
    delay(10);
  }
}

// Helper function to define scroll area
void defineScrollArea(uint16_t topFixedArea, uint16_t scrollArea, uint16_t bottomFixedArea) {
  tft.writecommand(0x33); // VSCRDEF command
  tft.writedata(topFixedArea >> 8);
  tft.writedata(topFixedArea);
  tft.writedata(scrollArea >> 8);
  tft.writedata(scrollArea);
  tft.writedata(bottomFixedArea >> 8);
  tft.writedata(bottomFixedArea);
}

// Helper function to scroll the display
void scrollDisplay(uint16_t scrollValue) {
  tft.writecommand(0x37); // VSCRSADD command
  tft.writedata(scrollValue >> 8);
  tft.writedata(scrollValue & 0xFF);
}

// Demo 3: Display rotation using direct MADCTL command
void rotationDemo() {
  // MADCTL values for different rotations
  const uint8_t MADCTL_PORTRAIT = 0x00;         // 0 degrees
  const uint8_t MADCTL_LANDSCAPE = 0x60;        // 90 degrees
  const uint8_t MADCTL_PORTRAIT_FLIPPED = 0xC0; // 180 degrees
  const uint8_t MADCTL_LANDSCAPE_FLIPPED = 0xA0; // 270 degrees
  
  // Array of rotation values and names
  uint8_t rotations[] = {MADCTL_PORTRAIT, MADCTL_LANDSCAPE, MADCTL_PORTRAIT_FLIPPED, MADCTL_LANDSCAPE_FLIPPED};
  const char* rotationNames[] = {"Portrait", "Landscape", "Portrait Flipped", "Landscape Flipped"};
  
  for (int i = 0; i < 4; i++) {
    tft.fillScreen(BLACK);
    
    // Set rotation directly using MADCTL command
    tft.writecommand(0x36); // MADCTL command
    tft.writedata(rotations[i]);
    
    // Draw orientation indicator
    tft.drawRect(0, 0, tft.width(), tft.height(), RED);
    tft.fillTriangle(tft.width()/2, 0, tft.width()/2 - 10, 20, tft.width()/2 + 10, 20, RED);
    
    // Display rotation name
    tft.setCursor(tft.width()/2 - 80, tft.height()/2 - 10);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.println(rotationNames[i]); 
    
    delay(1500);
  }
  
  // Reset to landscape mode
  tft.setRotation(1);
}

// Demo 4: Partial display mode
void partialDisplayDemo() {
  tft.fillScreen(BLACK);
  
  // Draw full screen content
  for (int y = 0; y < tft.height(); y += 20) {
    tft.drawFastHLine(0, y, tft.width(), BLUE);
  }
  
  for (int x = 0; x < tft.width(); x += 20) {
    tft.drawFastVLine(x, 0, tft.height(), BLUE);
  }
  
  tft.setCursor(20, 30);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.println("Full Screen Mode"); 
  
  delay(1500);
  
  // Define partial area (middle portion of screen)
  uint16_t startRow = 80;
  uint16_t endRow = 160;
  
  // Set partial area
  tft.writecommand(0x30); // PTLAR command
  tft.writedata(startRow >> 8);
  tft.writedata(startRow);
  tft.writedata(endRow >> 8);
  tft.writedata(endRow);
  
  // Enable partial mode
  tft.writecommand(0x12); // PTLON command
  
  tft.setCursor(20, 120);
  tft.setTextColor(RED);
  tft.setTextSize(2);
  tft.println("Partial Mode"); 
  
  delay(2000);
  
  // Return to normal mode
  tft.writecommand(0x13); // NORON command
  
  tft.setCursor(20, 200);
  tft.setTextColor(GREEN);
  tft.setTextSize(2);
  tft.println("Back to Normal"); 
}

// Demo 5: Brightness control (if supported by display)
void brightnessDemo() {
  tft.fillScreen(BLACK);
  
  tft.setCursor(20, 30);
  tft.setTextColor(WHITE);
  tft.setTextSize(2);
  tft.println("Brightness Control"); 
  tft.println("(if supported)"); 
  
  // Draw a colorful test pattern
  for (int i = 0; i < 6; i++) {
    uint16_t colors[] = {RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN};
    tft.fillRect(40 + i*40, 100, 30, 100, colors[i]);
  }
  
  // Try different brightness levels
  for (int brightness = 0; brightness <= 255; brightness += 51) {
    // Set brightness using WRDISBV command
    tft.writecommand(0x51); // WRDISBV command
    tft.writedata(brightness);
    
    tft.fillRect(20, 220, 280, 30, BLACK);
    tft.setCursor(20, 220);
    tft.setTextColor(WHITE);
    tft.setTextSize(2);
    tft.print("Brightness: "); 
    tft.print(brightness * 100 / 255);
    tft.println("%");
    
    delay(1000);
  }
  
  // Reset to full brightness
  tft.writecommand(0x51); // WRDISBV command
  tft.writedata(255);
}
