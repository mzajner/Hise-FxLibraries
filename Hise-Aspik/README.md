# Hise Aspik

This project is a HISE wrapper library for ASPiK and Will Pirkle style DSP examples.

The local project contains a broad collection of wrapper headers in `AdditionalSourceCode/nodes`, while the current scriptnode network example is a minimal test network named `tester_ScriptFx`.

## FX Included

The local wrappers cover these main groups:

- Delay
  - `AspikDelayAnalog`
  - `AspikDelayDigital`
  - `AspikDelayDuck`
  - `AspikDelayLcr`
  - `AspikDelayMultitap`
  - `AspikDelayStereo`
  - `AspikModDelay`
  - `AspikModDelayAdvanced`

- Dynamics
  - `AspikDynamicsCore`
  - `AspikDynamicsCrossover`
  - `AspikDynamicsFeedback`
  - `AspikDynamicsFiniteGate`
  - `AspikDynamicsLookahead`
  - `AspikDynamicsMultibandComp`
  - `AspikDynamicsParallel`

- Filters
  - `AspikFilterAllpass`
  - `AspikFilterAnalogFIR`
  - `AspikFilterBiquad`
  - `AspikFilterButterworth`
  - `AspikFilterImpulseInvariant`
  - `AspikFilterIntegrationDiff`
  - `AspikFilterLadder`
  - `AspikFilterLinkwitzRiley`
  - `AspikFilterMA`
  - `AspikFilterMMA`
  - `AspikFilterPeak`
  - `AspikFilterPole`
  - `AspikFilterResonance`
  - `AspikFilterRlc`
  - `AspikFilterShelf`
  - `AspikFilterSvf`
  - `AspikFilterTemplate`
  - `AspikFilterVa1st`
  - `AspikFilterVicanek`

- Modulation
  - `AspikModFilter`
  - `AspikModOsc`
  - `AspikModPhaser`
  - `AspikModTremolo`

- Reverb
  - `AspikReverbDattorro`
  - `AspikReverbFdn`
  - `AspikReverbMoorer`
  - `AspikReverbSchroeder`
  - `AspikReverbTank`

- Utility and synthesis helpers
  - `AspikUtilEnvFollower`
  - `AspikUtilLfo`
  - `AspikUtilLooper`
  - `AspikPhaseVocoderRobotizer`

- Waveshaping and distortion
  - `AspikWaveshaperBitcrush`
  - `AspikWaveshaperFuzzFace`
  - `AspikWaveshaperOctaveUp`
  - `AspikWaveshaperTriode`
  - `AspikWaveshaperTubeClassB`
  - `AspikWaveshaperTubePreamp`
  - `AspikWaveshaperVirtualBass`

## Build

The easiest way to build this project is from inside HISE.

1. Open the project in HISE
2. Use the top toolbar and choose `Export`
3. Choose `Compile DSP networks as dll`

## Credits

- original framework: [ASPiK](https://github.com/willpirkleaudio/ASPiK)
- original author: Will Pirkle and Tritone Systems
- related project gallery: [Will Pirkle FX Project Gallery](https://www.willpirkle.com/fx-book/project-gallery/)

## License Note

ASPiK is not a simple MIT style dependency. The upstream repository presents a modified BSD license together with a limited SDK license agreement and branding restrictions. Review the upstream terms before redistributing source wrappers or repackaging the SDK itself.

See [THIRD_PARTY_NOTICES.md](/Users/ernest/HisePersonal/Personal/Hise-FxLibraries/Hise-Aspik/THIRD_PARTY_NOTICES.md).
