# Hise Faust

This project is a HISE wrapper library for Faust based effects and processors.

The local project contains a broad collection of Faust derived wrapper headers in `AdditionalSourceCode/nodes`. The current example network is a simple test network named `asdf` that instantiates the `FuzzTone` class.

## FX Included

The local wrappers include processors such as:

- `FuzzTone`
- `Compressor`
- `Compressor1176`
- `DynamicRangeCompressor`
- `EchoplexDelay`
- `Greyhole`
- `Phaser`
- `FlangerFeedback`
- `TransientShaper`
- `SoftClip`
- `SaturatorWavefolding`
- `PowerAmp`
- `SpeakerSimulator`
- `StereoWidth`
- `RingModulation`
- `Vocoder1`
- `granulator`
- `freeverb`
- `zitaRev`

The folder also includes multiple analog style filter models and several delay, reverb, modulation, and distortion processors.

## Build

The easiest way to build this project is from inside HISE.

1. Open the project in HISE
2. Use the top toolbar and choose `Export`
3. Choose `Compile DSP networks as dll`

## Credits

- upstream Faust ecosystem: [Faust](https://github.com/grame-cncm/faust)
- related tooling reference: [Faust IDE](https://github.com/grame-cncm/faustide)
- original organization: GRAME

## License Note

Faust tooling is not a simple permissive dependency by default. The upstream Faust compiler repository publishes the compiler under the GNU Lesser General Public License version 2.1 or later. If you redistribute wrappers, generated code, or linked libraries, verify the exact obligations for the specific Faust and HISE modules you are shipping.

This folder also looks like a mixed wrapper collection, so it is a good idea to check the original author of each processor or example before publishing derived work.

See [THIRD_PARTY_NOTICES.md](/Users/ernest/HisePersonal/Personal/Hise-FxLibraries/Hise-Faust/THIRD_PARTY_NOTICES.md).
