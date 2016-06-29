import root;
import pad_layout;
include "../run_info.asy";

string topDir = "../../";

string run = "275125";

string rp = "3";

string plane = "3";

xSizeDef = 12cm;

drawGridDef = false;

//----------------------------------------------------------------------------------------------------

NewPad("strip");

RootGetObject(topDir + run + "/distributions.root", rp + "/plane distributions/inclusive/h_dist_" + plane);
draw(robj, "vl", red+1pt, "all events");

RootGetObject(topDir + run + "/distributions.root", rp + "/plane distributions/no cutoff/h_dist_" + plane);
draw(robj, "vl", blue+1pt, "only fully transmitted events");

yaxis(XEquals(128, false), dashed);
yaxis(XEquals(256, false), dashed);
yaxis(XEquals(384, false), dashed);

real y_label = 8000;
label("vfat 0", (128*0 + 128/2, y_label));
label("vfat 1", (128*1 + 128/2, y_label));
label("vfat 2", (128*2 + 128/2, y_label));
label("vfat 3", (128*3 + 128/2, y_label));

AttachLegend("run " + run + ", RP " + rp + ", plane " + plane, W, W);
