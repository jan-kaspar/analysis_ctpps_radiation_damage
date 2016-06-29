import root;
import pad_layout;
include "../run_info.asy";

string topDir = "../../";

string run = "275125";

string rp = "3";

string plane = "3";

string vfat = "3";

xSizeDef = 12cm;

//----------------------------------------------------------------------------------------------------

NewPad("cluster multiplicity");
scale(Linear, Log);

RootGetObject(topDir + run + "/distributions.root", rp + "/vfat distributions/plane " + plane + "/vfat " + vfat + "/h_multiplicity_cluster");
draw(robj, "vl", blue+1pt, "reconstructed in SW");

RootGetObject(topDir + run + "/distributions.root", rp + "/vfat distributions/plane " + plane + "/vfat " + vfat + "/h_multiplicity_daq");
draw(robj, "vl", red+1pt, "transmitted by DAQ");

yaxis(XEquals(8, false), dashed);

AttachLegend("run " + run + ", RP " + rp + ", plane " + plane + ", vfat " + vfat, NE, NE);
