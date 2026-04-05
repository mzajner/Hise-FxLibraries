# Hise PointToPoint

This project is a HISE wrapper library for the Hack Audio PointToPoint SDK.

The local folder contains a very large wrapper set for analog circuit models, tone stacks, filters, EQ sections, clipping stages, and pedal style circuits. It looks like a wrapper library and generation sandbox more than a finished end user plugin.

## FX Included

The local wrappers include large groups such as:

- amplifier tone stacks
- guitar pedal stages
- clipping circuits
- static tube and transistor stages
- Baxandall and graphic EQ circuits
- high pass low pass band pass and notch filters
- state variable and Sallen Key filters

Representative wrappers include:

- `PtpTubeScreamerToneStage`
- `PtpElectraDistortion`
- `PtpProCoRat`
- `PtpMarshallGuvnorToneControl`
- `PtpBigMuffToneStage`
- `PtpSevenBandGraphicEQ`
- `PtpFourBandEQ`
- `PtpVariableFrequencyVariableQMidEQ`
- `PtpFirstOrderStateVariableHPF`
- `PtpButterworthSallenKeyLPF`

The local generation helpers also live in `docs`.

## Build

The easiest way to build this project is from inside HISE.

1. Open the project in HISE
2. Use the top toolbar and choose `Export`
3. Choose `Compile DSP networks as dll`

## Credits

- upstream SDK: [HackAudio PointToPoint SDK](https://github.com/HackAudio/PointToPoint_SDK)
- original company: Hack Audio LLC

## License Note

PointToPoint uses a restrictive commercial style license agreement, not a permissive open source license. Review the upstream terms carefully before publishing source, headers, static libraries, or wrapper builds.

See [THIRD_PARTY_NOTICES.md](/Users/ernest/HisePersonal/Personal/Hise-FxLibraries/Hise-PointToPoint/THIRD_PARTY_NOTICES.md).
