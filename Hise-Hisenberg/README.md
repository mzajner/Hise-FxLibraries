# Hise Hisenberg

This project is a HISE wrapper library for personal custom effects by Ernest.

This folder is the home for my personal custom effect library inside HISE. It is more of a DSP toolbox than a single finished plugin, and the real value is the custom node set in `AdditionalSourceCode/nodes`.

## FX Included

The local custom processors include:

- `sslCompressor`
- `sslGate`
- `sslEqExternal`
- `transient_designer`
- `peakLimiter`
- `comp1`
- `autogain`
- `hard_clip`
- `soft_clip`

It also includes a VHS style processing group:

- `vhs_compander`
- `vhs_degradation`
- `vhs_dropout`
- `vhs_modulation`
- `vhs_noiseGenerator`
- `vhs_peakLimiter`
- `vhs_pitchMods`
- `vhs_postEq`
- `vhs_Loss`

Support modules include:

- `fft_analyzer`
- `Butterworth2ndHpf`

## Build

The easiest way to build this project is from inside HISE.

1. Open the project in HISE
2. Use the top toolbar and choose `Export`
3. Choose `Compile DSP networks as dll`

## Credits

- local project author: Ernest
- source family: personal custom DSP library

## License Note

This project is licensed under GPL 3.0.
