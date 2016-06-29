import root;
import pad_layout;
include "run_info.asy";

string topDir = "../";

string rp = "3";

string runs[] = {
	"274199",
    "274241",
    "274244",
    "274388",
    "274422",
    "274958",
    "274969",
    "274999",
    "275125",
    "275310",
    "275345",
    "275376",
    "275783",
    "275836",
};


string runs[] = {
    "275783",
    "275836",
};


//----------------------------------------------------------------------------------------------------

for (int ri : runs.keys)
{
	write(runs[ri]);

	NewRow();

	RunInfo rInfo = GetRunInfoByRun(runs[ri]);

	NewPad(false);
	label("{\SetFontSizesXX \vbox{\hbox{" + rInfo.date + "}\hbox{fill " + rInfo.fill + "}\hbox{run " + rInfo.run + "}}}");

	// plane distributions
	NewPad("strip in plane 2");
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/plane distributions/no cutoff/h_dist_2");
	draw(robj, "vl", heavygreen+1pt);
	xlimits(240, 450, Crop);
	yaxis(XEquals(256, false), dashed);
	yaxis(XEquals(384, false), dashed);

	NewPad("strip in plane 3");
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/plane distributions/no cutoff/h_dist_3");
	draw(robj, "vl", magenta+1pt);
	xlimits(240, 450, Crop);
	yaxis(XEquals(256, false), dashed);
	yaxis(XEquals(384, false), dashed);

	// plane correlations
	NewPad("strip in plane 2", "strip in plane 3");
	scale(Linear, Linear, Log);
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/plane correlations/no cutoff/h2_plane_corr_32");

	TH2_x_min = 300; TH2_x_max = 410;
	TH2_y_min = 350; TH2_y_max = 440;
	draw(robj);
	
	limits((TH2_x_min, TH2_y_min), (TH2_x_max, TH2_y_max), Crop);
}

GShipout(vSkip=0mm);
