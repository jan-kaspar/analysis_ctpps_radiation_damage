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
//    "275783",
//    "275836",
};

string runs[] = {
	"274199",
    //"274422",
    "275125",
    "275376",
};


//----------------------------------------------------------------------------------------------------

for (int ri : runs.keys)
{
	write(runs[ri]);

	NewRow();

	RunInfo rInfo = GetRunInfoByRun(runs[ri]);

	NewPad(false);
	label("{\SetFontSizesXX \vbox{\hbox{fill " + rInfo.fill + "}\hbox{run " + rInfo.run + "}}}");

	// active planes
	/*
	NewPad("N planes on");
	scale(Linear, Log);
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/h_n_planes_on");
	draw(robj, "vl", black+1pt);
	*/

	// plane distributions
	NewPad("strip in plane 2");
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/plane distributions/inclusive/h_dist_2");
	draw(robj, "vl", heavygreen+1pt);
	//RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/plane distributions/no cutoff/h_dist_2");
	//draw(robj, "vl", heavygreen+1pt);
	xlimits(240, 450, Crop);
	yaxis(XEquals(256, false), dashed);
	yaxis(XEquals(384, false), dashed);

	NewPad("strip in plane 3");
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/plane distributions/inclusive/h_dist_3");
	draw(robj, "vl", magenta+1pt);
	//RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/plane distributions/no cutoff/h_dist_3");
	//draw(robj, "vl", magenta+1pt);
	xlimits(240, 450, Crop);
	yaxis(XEquals(256, false), dashed);
	yaxis(XEquals(384, false), dashed);

	// plane correlations
	NewPad("strip in plane 2", "strip in plane 3");
	scale(Linear, Linear, Log);
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/plane correlations/inclusive/h2_plane_corr_32");

	TH2_x_min = 300; TH2_x_max = 410;
	TH2_y_min = 350; TH2_y_max = 440;
	draw(robj);
	
	limits((TH2_x_min, TH2_y_min), (TH2_x_max, TH2_y_max), Crop);

	// vfat distributions
	NewPad("cluster multiplicity in plane 2, vfat 2");
	scale(Linear, Log);
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/vfat distributions/plane 2/vfat 2/h_multiplicity_cluster");
	draw(robj, "vl", heavygreen+1pt);
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/vfat distributions/plane 2/vfat 2/h_multiplicity_daq");
	draw(robj, "vl", heavygreen+dashed);
	yaxis(XEquals(8, false), dashed);
	
	/*
	NewPad("cluster multiplicity in plane 3, vfat 3");
	scale(Linear, Log);
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/vfat distributions/plane 3/vfat 3/h_multiplicity_cluster");
	draw(robj, "vl", magenta+1pt);
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/vfat distributions/plane 3/vfat 3/h_multiplicity_daq");
	draw(robj, "vl", magenta+dashed);
	yaxis(XEquals(8, false), dashed);
	*/

	NewPad("cluster size in plane 2, vfat 2");
	scale(Linear, Log);
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/vfat distributions/plane 2/vfat 2/h_cluster_size");
	draw(robj, "vl", heavygreen+1pt);

	/*
	NewPad("cluster size in plane 3, vfat 3");
	scale(Linear, Log);
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/vfat distributions/plane 3/vfat 3/h_cluster_size");
	draw(robj, "vl", magenta+1pt);
	*/

	// patterns
	/*
	NewPad("N patterns U");
	scale(Linear, Log);
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/h_n_patterns_U");
	draw(robj, "vl", red+1pt);
	
	NewPad("N patterns V");
	scale(Linear, Log);
	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/h_n_patterns_V");
	draw(robj, "vl", blue+1pt);
	*/

	// xy plot with tracks
	/*
	NewPad("$x\ung{mm}$", "$y\ung{mm}$");
	scale(Linear, Linear, Log);

	RootGetObject(topDir + runs[ri] + "/distributions.root", rp + "/h2_y_vs_x");

	TH2_x_min = 6; TH2_x_max = 14;
	TH2_y_min = -1.5; TH2_y_max = +1.5;
	draw(robj);

	limits((TH2_x_min, TH2_y_min), (TH2_x_max, TH2_y_max), Crop);
	*/
}
