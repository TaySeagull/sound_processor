#include <iostream>
#include "waveform.h"

int main() {
    std::cout << "Sound Processor";
    
    Waveform waveform;
    std::cout << "Sample rate: " << waveform.getSampleRate() << "\n";
    std::cout << "Channels: " << waveform.getChannels() << "\n";
    std::cout << "Bits per sample: " << waveform.getBitsPerSample() << "\n";
    
    return 0;
}