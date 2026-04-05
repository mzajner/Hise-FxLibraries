/* Stereo delay with feedback. */

declare name "echo";
declare description "stereo delay effect";
declare author "Albert Graef";
declare version "1.0";

import("music.lib");
import("stdfaust.lib");

level		= hslider("level", 1, 0, 1, 0.01):si.smoo;
dtime		= hslider("delay", 1, 0, 5, 0.001):si.smoo;
feedback	= hslider("feedback", 0, 0, 0.95
, 0.001):si.smoo;
stereo		= hslider("stereo", 0, 0, 1, 0.001):si.smoo;

/* The stereo parameter controls the amount of stereo spread. For stereo=0 you
   get a plain delay, without crosstalk between the channels. For stereo=1 you
   get a pure ping-pong delay where the echos from the left first appear on
   the right channel and vice versa. Note that you'll hear the stereo effects
   only if the input signal already has some stereo spread to begin with; if
   necessary, you can just pan the input signal to the left or the right to
   achieve that. */

echo(dtime,level,feedback,stereo,x,y)
		= f(x,y) // the echo loop
		// mix
		: (\(u,v).(x+level*(d(u)+c(v)),
			   y+level*(d(v)+c(u))))
		// compensate for gain level
		: (/(1+level), /(1+level))
with {
	f	= g ~ (*(feedback),*(feedback));
	g(u,v,x,y)
		= h(x+d(u)+c(v)), h(y+d(v)+c(u));
	h	= fdelay(1<<18, SR*dtime);
	c(x)	= x*stereo;
	d(x)	= x*(1-stereo);
};

process		= vgroup("echo", echo(dtime,level,feedback,stereo));