#include <string>
#include <vector>

//----------------------------------------------------------------------------------------------------

std::vector<std::string> input_files;

std::string input_ntuple_name;

void InitInputFiles()
{
	input_ntuple_name = "TotemNtuple";

	input_files.clear();

	std::string prefix = "/afs/cern.ch/work/j/jkaspar/software/ctpps/production/develop/CMSSW_8_1_0_pre5/user/reconstruction/work_dir/multiple_runs_3/";
	prefix += "274958/";

	for (int idx = 0; idx <= 6; ++idx)
	{
		char buf[100];
		sprintf(buf, "%i", idx);

		input_files.push_back(prefix + buf + "/reco.root");
	}
}
