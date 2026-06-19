# Hise Airwindows

This project is a HISE wrapper library for a large collection of Airwindows processors by Chris Johnson.

The local project is mainly wrapper based. 

## Main Wrapper

The main wrapper entry point is:

- [Airwindows.h](/Users/ernest/HisePersonal/Personal/Hise-FxLibraries/Hise-Airwindows/DspNetworks/ThirdParty/src/airwindows/AirWindows.h)

That factory registers a large set of Airwindows nodes such as console processors, saturation, dynamics, EQ, delay, reverb, modulation, utility, and dither tools.

Examples of included wrappers:

- `Console` family
- `Purest` family
- `Galactic` family
- `IronOxide` family
- `Pressure` family
- `PitchDelay`
- `PocketVerbs`
- `MatrixVerb`
- `MidSide`
- `SampleDelay`

## Build

The easiest way to build this project is from inside HISE.

1. Open the project in HISE
2. Use the top toolbar and choose `Export`
3. Choose `Compile DSP networks as dll`

## Credits

- original author: Chris Johnson
- original project: [Airwindows](https://github.com/airwindows/airwindows)

## License Note

Airwindows is published under the MIT license. Preserve the original copyright notice and link back to the upstream project when redistributing wrappers or derived builds.

See [THIRD_PARTY_NOTICES.md](/Users/ernest/HisePersonal/Personal/Hise-FxLibraries/Hise-Airwindows/THIRD_PARTY_NOTICES.md).
