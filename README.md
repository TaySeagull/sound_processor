# sound_processor

The project is a CLI application that processes a WAV audio file supplied as input. The resulting file is processed through a chain of filters (a pipeline), the set and characteristics of which are also passed to the application via command-line video parameters. The filters in the pipeline sequentially transform the audio data of the source file.

### Examples of transformations performed by the filters:
- Modifying the amplitude characteristics of a sound wave (parametrically changing  sound volume, inserting silent fragments—pauses, normalizing sound);
- Simple changes to the frequency-time characteristics of a sound wave (compression, stretching of a sound fragment);
- Generation of simple parametric sound signals (sinusoids);
- Generation of an amplitude-modulated parametric sound signal;
- Generation of a frequency-modulated parametric sound signal;
- Application of simple implementations of parametric filters: low-pass (LPF), high-pass (HPF), band-pass, and notch filters.

### Project structure
```c++
├── include/
│   ├── wav_reader.h
│   ├── wav_writer.h
│   ├── wave_structures.h
│   ├── waveform.h
├── src/
│   ├── main.cpp
│   ├── wav_reader.cpp
│   ├── wav_writer.cpp
│   ├── waveform.cpp
├── tests/
│   ├── CMakeLists.txt
│   ├── test_wav_reader.cpp
│   ├── test_wav_writer.cpp
│   ├── test_waveform.cpp
├── CMakeLists.txt
└── README.md
```

### Build and lauch

1. Build
```c++
cmake ..
cmake --build .
```

2. Testing
- Class Waveform
    ```c++
    ./build/tests/sound_processor_tests
    ```
