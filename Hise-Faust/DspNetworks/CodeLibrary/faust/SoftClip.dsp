import("stdfaust.lib");
import("aanl.lib");
import("maths.lib");
import("basics.lib");

process = driver : wrapper : softclip : aa.hardclip2 : trimmer;

driver(x) = x * drive * squeeze;
trimmer(x) = x * (1 / squeeze);
wrapper(x) = (clipper(x) * fadeamt) + (x * (1 - fadeamt));
clipper(x) = aa.arctan(clipamt * x)/aa.arctan(clipamt);

drive = db2linear(nentry("drive", 0, 0, 1, 0.01) * 20) : si.smoo;
squeeze = db2linear(nentry("squeeze", 0, 0, 1, 0.01) * 20) : si.smoo;
//trim = db2linear((nentry("trim", 0, 0, 1, 0.01) * 20) - 20);

slider_raw = nentry("clipping", 0, 0, 1, 0.01);
slider = (.85*slider_raw)+0.15;
fadeamt = min(20*slider_raw, 1);
clipamt = max(ma.EPSILON, (slider^2)*20);

softclip = softclipamt, _ : softclip_maths ; 
softclip_maths( a1, x ) = min( a0 , atan((a0 - a1)/a2 ) * a2 + a1 ) * a3
  with{
    a0 = abs(x);
    a2 = (1-a1) * 2/ma.PI ;
    a3 = ma.signum(x) ;
  };

softclipamt = db2linear(nentry("softclip", 0, 0, 1, 0.01) * -3) : si.smoo;