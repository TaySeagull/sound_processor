# sound_processor

The project is a CLI application that processes a WAV audio file supplied as input. The resulting file is processed through a chain of filters (a pipeline), the set and characteristics of which are also passed to the application via command-line video parameters. The filters in the pipeline sequentially transform the audio data of the source file.

### Examples of transformations performed by the filters:

### Transformation filters

- **Amplifier Filter**
    Multiplies each sample by a constant factor
    - Usage: `-f ampl <factor>`

- **Normalize Filter**
    Scales signal so the maximum absolute sample equals a target fraction of 32767
    - Usage: `-f normalize [peak]`

- **Silence Filter**
    Inserts a segment of zero samples, shifting subsequent samples right
    - Usage: `-f silence <unit> <start> <end>`

- **Time Stretch Filter**
    Changes signal duration using linear interpolation
    - Usage: `-f timestretch <factor>`

- **Lowpass Filter**
    Smooths signal using moving average with fixed window size
    - Usage: `-f lowpass <window_size>`

### Generating filters

- **Sine Wave Generator**
    Generates a pure sine wave tone
    - Usage: `-f generator sin <frequency_hz> <duration_ms>`

- **Amplitude Modulation Generator**
    Amplitude-modulated signal. Volume oscillates by modulator frequency
    - Usage: `-f generator am <amplitude> <carrier_hz> <modulation_hz> <depth> <duration_ms>`

- **Frequency Modulation Generator**
    Frequency-modulated signal. Pitch deviates by modulator frequency
    - Usage: `-f generator fm <amplitude> <carrier_hz> <modulation_hz> <deviation_hz> <duration_ms>`


### Project structure
```c++
├── include/
│   ├── filters/
│       ├── abstract_generator_filter.h
│       ├── ampl_filter.h
│       ├── filter_descriptor.h
│       ├── filter_producers.h
│       ├── generator_filter.h
│       ├── lowpass_filter.h
│       ├── normalize_filter.h
│       ├── silence_filter.h
│       └── timestretch_filter.h
│   ├── application.h
│   ├── argument_parser.h
│   ├── cmd_line_args_2_pipeline_converter.h
│   ├── ifilter.h
│   ├── pipeline.h
│   ├── wav_reader.h
│   ├── wav_writer.h
│   ├── wave_structures.h
│   └── waveform.h
├── src/
├── filters/
│       ├── ampl_filter.cpp
│       ├── filter_producers.cpp
│       ├── generator_filter.cpp
│       ├── lowpass_filter.cpp
│       ├── normalize_filter.cpp
│       ├── silence_filter.cpp
│       └── timestretch_filter.cpp
│   ├── application.cpp
│   ├── argument_parser.cpp
│   ├── cmd_line_args_2_pipeline_converter.cpp
│   ├── main.cpp
│   ├── pipeline.cpp
│   ├── wav_reader.cpp
│   ├── wav_writer.cpp
│   └── waveform.cpp
├── tests/
│   ├── CMakeLists.txt
│   ├── mock_filter.h
│   ├── test_ampl_filter.cpp
│   ├── test_args_parser.cpp
│   ├── test_converter.cpp
│   ├── test_generator_filter.cpp
│   ├── test_lowpass_filter.cpp
│   ├── test_normalize_filter.cpp
│   ├── test_pipeline.cpp
│   ├── test_silence_filter.cpp
│   ├── test_timestretch_filter.cpp
│   ├── test_wav_reader.cpp
│   ├── test_wav_writer.cpp
│   ├── test_waveform.cpp
├── .gitignore
├── CMakeLists.txt
└── README.md
```

### Build and lauch

1. Build
```c++
cmake ..
cmake --build .
```
2. Lauch (example)
```c++
./sound_processor -o test_sin.wav -f generator sin 440 1000
```
3. Testing

    Options:
    - ["wav_reader"]
    - ["wav_writer"]
    - ["waveform"]
    - ["ampl_filter"]
    - ["timestretch"]
    - ["silence"]
    - ["lowpass"]
    - ["normalize"]
    - ["[generator][sin]"]
    - ["[generator][am]"]
    - ["[generator][fm]"]
    - ["args_parser"]
    - ["pipeline"]
    - ["converter"]

    ```c++
    ./tests/sound_processor_tests "[OPTIONS]"
    ```