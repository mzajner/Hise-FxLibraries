declare name "moogVCF";
declare description "Exercise and compare three Moog VCF implementations";

import("stdfaust.lib");

Q = hslider("Q",1,0,1,0.01):si.smoo;
normFreq = hslider("freq",0.1,0,1,0.001):si.smoo;
process = dm.moog_vcf_demo,dm.moog_vcf_demo;