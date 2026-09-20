#pragma once
struct MockSPI { void begin(int sck, int miso, int mosi, int cs); };
extern MockSPI SPI;
