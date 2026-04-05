import("stdfaust.lib");
bands = 32;
exFreq = hslider("Excitation Frequency[unit:Hz]",150,70,15000,0.01) : si.smoo;
attDuration = hslider("[0]Attack Duration[style:knob][unit:ms]",0.1,0.01,100,0.01)*0.001 : si.smoo;
relDuration = hslider("[1]Release Duration[style:knob][unit:ms]",1,0.01,100,0.01)*0.001 : si.smoo;
filtersQ = hslider("[2]Q[style:knob]",15,1,30,0.01) : si.smoo;
vocoder(nBands,att,rel,q,source,excitation) = source <: par(i,nBands,oneAnalysisBand(i) : 
	oneSynthesisBand(i)) :> _
with{
	oneAnalysisBand(j) = fi.resonbp(freq,q,1) : an.amp_follower_ud(att,rel)
	with{
		freq = 25*pow(2,(j+1)*(9/nBands));
	};
	
	oneSynthesisBand(j) = _,excitation : fi.resonbp(freq,q)
	with{
		freq = 25*pow(2,(j+1)*(9/nBands));
	};
};
process = (_,vgroup("[1]Sawtooth",os.sawtooth(exFreq)) : 
	hgroup("[0]Vocoder",vocoder(bands,attDuration,relDuration,filtersQ))), (_,vgroup("[1]Sawtooth",os.sawtooth(exFreq)) : 
	hgroup("[0]Vocoder",vocoder(bands,attDuration,relDuration,filtersQ)));