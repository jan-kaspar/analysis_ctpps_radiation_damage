import root;
import pad_layout;
include "run_info.asy";

string topDir = "../";

string rps[] = {
	"3",
	"2",
	"102",
	"103",
};

string rp_labels[] = {
	"45-210-F-H",
	"45-210-N-H",
	"56-210-N-H",
	"56-210-F-H",
};

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
    "274199",
    "274422",
    "275125",
    "275376",
};

TH2_x_min = 5.5; TH2_x_max = 12.5;
TH2_y_min = -1.5; TH2_y_max = +1.5;
TH2_z_min = 1; TH2_z_max = 1e3;

xSizeDef = 10cm;

TH2_palette = Gradient(blue, heavygreen, yellow, red, black);

//----------------------------------------------------------------------------------------------------

NewPad(false);
for (int rpi : rps.keys)
{
	NewPad(false);
	label("{\SetFontSizesXX " + rp_labels[rpi] + "}");
}

for (int ri : runs.keys)
{
	write(runs[ri]);

	NewRow();

	RunInfo rInfo = GetRunInfoByRun(runs[ri]);

	NewPad(false);
	label("{\SetFontSizesXX \vbox{\hbox{" + rInfo.date + "}\hbox{fill " + rInfo.fill + "}\hbox{run " + rInfo.run + "}}}");

	for (int rpi : rps.keys)
	{
		NewPad("$x\ung{mm}$", "$y\ung{mm}$", axesAbove=true);
		scale(Linear, Linear, Log);

		RootGetObject(topDir + runs[ri] + "/distributions.root", rps[rpi] + "/h2_y_vs_x");
		draw(robj);

		limits((TH2_x_min, TH2_y_min), (TH2_x_max, TH2_y_max), Crop);
	}
}

//----------------------------------------------------------------------------------------------------

GShipout(hSkip=0mm, vSkip=0mm);
