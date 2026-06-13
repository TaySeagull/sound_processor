# sound_processor

The project is a CLI application that processes a WAV audio file supplied as input. The resulting file is processed through a chain of filters (a pipeline), the set and characteristics of which are also passed to the application via command-line video parameters. The filters in the pipeline sequentially transform the audio data of the source file.

### Examples of transformations performed by the filters:

- **Amplifier Filter** - Adjusts the volume/amplitude of the audio signal
- **Time Stretch Filter** - Changes the playback speed of the audio
- **Silence Filter** - Replaces a specific segment of the audio with silence (zero samples)
- **Sine Wave Generator** - Generates a pure sine wave tone
- **Amplitude Modulation Generator** - Generates an amplitude-modulated signal where the volume oscillates according to a modulator frequency
- **Frequency Modulation Generator** - enerates a frequency-modulated signal where the pitch oscillates according to a modulator frequency


### Project structure
```c++
├── include/
│   ├── include/abstract_generator_filter.h
│   ├── am_filter.h
│   ├── ampl_filter.h
│   ├── argument_parser.h
│   ├── filter_descriptor.h
│   ├── fm_filter.h
│   ├── ifilter.h
│   ├── pipeline.h
│   ├── silence_filter.h
│   ├── sin_gen_filter.h
│   ├── timestretch_filter.h
│   ├── wav_reader.h
│   ├── wav_writer.h
│   ├── wave_structures.h
│   ├── waveform.h
├── src/
│   ├── am_filter.cpp
│   ├── ampl_filter.cpp
│   ├── argument_parser.cpp
│   ├── fm_filter.cpp
│   ├── main.cpp
│   ├── pipeline.cpp
│   ├── silence_filter.cpp
│   ├── sin_gen_filter.cpp
│   ├── timestretch_filter.cpp
│   ├── wav_reader.cpp
│   ├── wav_writer.cpp
│   ├── waveform.cpp
├── tests/
│   ├── CMakeLists.txt
│   ├── mock_filter.h
│   ├── test_am_filter.cpp
│   ├── test_ampl_filter.cpp
│   ├── test_args_parser.cpp
│   ├── test_fm_filter.cpp
│   ├── test_pipeline.cpp
│   ├── test_silence_filter.cpp
│   ├── test_sin_gen_filter.cpp
│   ├── test_timestretch_filter.cpp
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
