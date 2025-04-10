# Architecture Documentation

## Overview

This Arduino project uses an ILI9341 TFT display controller to create a visual interface. The architecture follows a modular approach with clear separation of concerns.

## Technical Decisions

- **Arduino Platform**: Selected for its ease of use and extensive library support for hardware interfaces
- **ILI9341 Display**: Chosen for its color capabilities, resolution, and compatibility with Arduino
- **Library Selection**: Using Adafruit libraries for reliable display control and graphics rendering

## Component Structure

1. **Core Components**
   - Main Arduino sketch (entry point)
   - Display controller interface
   - Input handling module
   - Application logic

2. **Library Dependencies**
   - Adafruit GFX Library
   - Adafruit ILI9341 Library
   - SPI Library

## Data Flow

1. Arduino initializes and configures the display
2. User input is processed through input handlers
3. Application logic determines display output
4. Display controller renders the visual interface

## ILI9341 Display Controller Architecture

The ILI9341 is a 262,144-color single-chip SoC driver for a TFT liquid crystal display with resolution of 240RGB×320 dots. The controller consists of the following key components:

### Hardware Interface

- **SPI Communication Protocol**: Primary interface for Arduino communication
  - MOSI (Master Out Slave In): Data from Arduino to display
  - MISO (Master In Slave Out): Data from display to Arduino (rarely used)
  - SCK (Serial Clock): Clock signal for synchronizing data transfer
  - CS (Chip Select): Enables/disables the display controller
  - DC (Data/Command): Distinguishes between commands and data
  - RESET: Hardware reset pin (optional but recommended)

### Command Structure

The ILI9341 uses a command-based protocol over SPI with the following format:

1. Pull CS (Chip Select) LOW to begin communication
2. Set DC (Data/Command) pin LOW for commands, HIGH for data
3. Send command byte over SPI
4. Send any parameter bytes (with DC HIGH)
5. Pull CS HIGH to end communication

### Key Commands

- `0x01`: Software Reset
- `0x11`: Sleep Out
- `0x29`: Display ON
- `0x2A`: Column Address Set (X coordinates)
- `0x2B`: Page Address Set (Y coordinates)
- `0x2C`: Memory Write (pixel data)
- `0x36`: Memory Access Control (rotation, RGB/BGR order)
- `0x3A`: Pixel Format Set (color depth)

### Comprehensive Command List

| Command | Hex Code | Description | Parameters |
|---------|----------|-------------|------------|
| NOP | 0x00 | No Operation | None |
| SWRESET | 0x01 | Software Reset | None |
| RDDID | 0x04 | Read Display ID | None |
| RDDST | 0x09 | Read Display Status | None |
| RDDPM | 0x0A | Read Display Power Mode | None |
| RDDMADCTL | 0x0B | Read Display MADCTL | None |
| RDDCOLMOD | 0x0C | Read Display Pixel Format | None |
| RDDIM | 0x0D | Read Display Image Mode | None |
| RDDSM | 0x0E | Read Display Signal Mode | None |
| RDDSDR | 0x0F | Read Display Self-Diagnostic Result | None |
| SLPIN | 0x10 | Sleep In | None |
| SLPOUT | 0x11 | Sleep Out | None |
| PTLON | 0x12 | Partial Display Mode On | None |
| NORON | 0x13 | Normal Display Mode On | None |
| INVOFF | 0x20 | Display Inversion Off | None |
| INVON | 0x21 | Display Inversion On | None |
| GAMSET | 0x26 | Gamma Set | 1: Gamma curve (1-4) |
| DISPOFF | 0x28 | Display Off | None |
| DISPON | 0x29 | Display On | None |
| CASET | 0x2A | Column Address Set | 4: SC[15:8], SC[7:0], EC[15:8], EC[7:0] |
| PASET | 0x2B | Page Address Set | 4: SP[15:8], SP[7:0], EP[15:8], EP[7:0] |
| RAMWR | 0x2C | Memory Write | Variable: Pixel data |
| RAMRD | 0x2E | Memory Read | None |
| PTLAR | 0x30 | Partial Area | 4: SR[15:8], SR[7:0], ER[15:8], ER[7:0] |
| VSCRDEF | 0x33 | Vertical Scrolling Definition | 6: TFA[15:8], TFA[7:0], VSA[15:8], VSA[7:0], BFA[15:8], BFA[7:0] |
| TEOFF | 0x34 | Tearing Effect Line OFF | None |
| TEON | 0x35 | Tearing Effect Line ON | 1: Mode (0-1) |
| MADCTL | 0x36 | Memory Access Control | 1: Parameter byte |
| VSCRSADD | 0x37 | Vertical Scrolling Start Address | 2: VSP[15:8], VSP[7:0] |
| IDMOFF | 0x38 | Idle Mode Off | None |
| IDMON | 0x39 | Idle Mode On | None |
| PIXFMT | 0x3A | Pixel Format Set | 1: Color format (0x55 for 16-bit, 0x66 for 18-bit) |
| WRMEMCONT | 0x3C | Write Memory Continue | Variable: Pixel data |
| RDMEMCONT | 0x3E | Read Memory Continue | None |
| SETSCANTE | 0x44 | Set Tear Scanline | 2: STS[15:8], STS[7:0] |
| GETSCAN | 0x45 | Get Scanline | None |
| WRDISBV | 0x51 | Write Display Brightness | 1: Brightness value |
| RDDISBV | 0x52 | Read Display Brightness | None |
| WRCTRLD | 0x53 | Write CTRL Display | 1: Control bits |
| RDCTRLD | 0x54 | Read CTRL Display | None |
| WRCABC | 0x55 | Write Content Adaptive Brightness Control | 1: CABC value |
| RDCABC | 0x56 | Read Content Adaptive Brightness Control | None |
| WRCABCMIN | 0x5E | Write CABC Minimum Brightness | 1: CABC minimum |
| RDCABCMIN | 0x5F | Read CABC Minimum Brightness | None |
| RDID1 | 0xDA | Read ID1 | None |
| RDID2 | 0xDB | Read ID2 | None |
| RDID3 | 0xDC | Read ID3 | None |

### MADCTL (0x36) Parameter Bits

The Memory Access Control (MADCTL) command is particularly important as it controls the display orientation:

| Bit | Name | Description when set (1) |
|-----|------|--------------------------|
| 7 | MY | Row Address Order (1 = Bottom to top) |
| 6 | MX | Column Address Order (1 = Right to left) |
| 5 | MV | Row/Column Exchange (1 = Exchange) |
| 4 | ML | Vertical Refresh Order (1 = Bottom to top) |
| 3 | BGR | RGB/BGR Order (0 = RGB, 1 = BGR) |
| 2 | MH | Horizontal Refresh Order (1 = Right to left) |
| 1-0 | - | Reserved (should be 0) |

Common MADCTL values for different rotations:

- Portrait (0°): 0x00 or 0x08 (BGR)
- Landscape (90°): 0x60 or 0x68 (BGR)
- Portrait flipped (180°): 0xC0 or 0xC8 (BGR)
- Landscape flipped (270°): 0xA0 or 0xA8 (BGR)

### Initialization Sequence

A proper initialization sequence is critical:

1. Hardware reset (toggle RESET pin)
2. Software reset (command 0x01)
3. Power control settings
4. Sleep out (command 0x11)
5. Set pixel format (command 0x3A)
6. Set memory access control (command 0x36)
7. Display on (command 0x29)

### Drawing Process

To draw on the display:

1. Set column address (command 0x2A) with start/end X coordinates
2. Set page address (command 0x2B) with start/end Y coordinates
3. Send memory write command (0x2C)
4. Send color data for each pixel (16-bit or 18-bit color format)

### Code Implementation

The Arduino code will implement these operations through a series of functions:

```cpp
// Send command to the display
void writeCommand(uint8_t cmd) {
  digitalWrite(DC_PIN, LOW);  // Command mode
  digitalWrite(CS_PIN, LOW);  // Select display
  SPI.transfer(cmd);         // Send command
  digitalWrite(CS_PIN, HIGH); // Deselect display
}

// Send data to the display
void writeData(uint8_t data) {
  digitalWrite(DC_PIN, HIGH); // Data mode
  digitalWrite(CS_PIN, LOW);  // Select display
  SPI.transfer(data);        // Send data
  digitalWrite(CS_PIN, HIGH); // Deselect display
}

// Set the drawing window
void setAddrWindow(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
  // Column address set
  writeCommand(0x2A);
  writeData(x0 >> 8);     // Start column high byte
  writeData(x0 & 0xFF);   // Start column low byte
  writeData(x1 >> 8);     // End column high byte
  writeData(x1 & 0xFF);   // End column low byte
  
  // Page address set
  writeCommand(0x2B);
  writeData(y0 >> 8);     // Start page high byte
  writeData(y0 & 0xFF);   // Start page low byte
  writeData(y1 >> 8);     // End page high byte
  writeData(y1 & 0xFF);   // End page low byte

  // Memory write
  writeCommand(0x2C);
}
```

### Memory Organization

The ILI9341 has internal GRAM (Graphics RAM) organized as a 240×320 pixel matrix. Each pixel can be represented in various color formats:

- 16-bit (65K colors): 5 bits red, 6 bits green, 5 bits blue (default)
- 18-bit (262K colors): 6 bits each for red, green, and blue

### Performance Considerations

- Use hardware SPI for fastest communication
- Batch pixel updates when possible
- Consider using the display's built-in scrolling and area fill commands
- For complex graphics, use buffering techniques to reduce flicker

## Future Considerations

- Potential for adding additional sensors
- Memory optimization for complex graphics
- Performance improvements for animation

Last updated: April 9, 2025
