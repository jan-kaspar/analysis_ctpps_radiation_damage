struct RunInfo
{
	string run;
	string fill;
	string date;
};

RunInfo[] runInfo;

RunInfo GetRunInfoByRun(string r)
{
	for (RunInfo i : runInfo)
	{
		if (i.run == r)
			return i;
	}

	RunInfo i;
	i.run = "unknown";
	i.fill = "unknown";
	return i;
}

void AddRunInfo(string d, string f, string r)
{
	RunInfo i;
	i.run = r;
	i.fill = f;
	i.date = d;

	runInfo.push(i);
}

//----------------------------------------------------------------------------------------------------

AddRunInfo("29 May 2016", "4961", "274199");
AddRunInfo("30 May 2016", "4964", "274241");
AddRunInfo("30 May 2016", "4964", "274244");
AddRunInfo("31 May 2016", "4965", "274251");
AddRunInfo( "1 Jun 2016", "4976", "?");
AddRunInfo( "1 Jun 2016", "4979", "274319");
AddRunInfo( "2 Jun 2016", "4980", "?");
AddRunInfo( "3 Jun 2016", "4984", "274382");
AddRunInfo( "3 Jun 2016", "4985", "274388");
AddRunInfo( "4 Jun 2016", "4988", "274422");
AddRunInfo( "5 Jun 2016", "4990", "?");
AddRunInfo("11 Jun 2016", "5005", "274958");
AddRunInfo("11 Jun 2016", "5013", "274969");
AddRunInfo("13 Jun 2016", "5017", "274999");
AddRunInfo("14 Jun 2016", "5020", "?");
AddRunInfo("15 Jun 2016", "5021", "275125");
AddRunInfo("16 Jun 2016", "5024", "?");
AddRunInfo("17 Jun 2016", "5026", "275310");
AddRunInfo("18 Jun 2016", "5027", "?");
AddRunInfo("19 Jun 2016", "5028", "275345");
AddRunInfo("19 Jun 2016", "5029", "?");
AddRunInfo("19 Jun 2016", "5030", "275376");
AddRunInfo("23 Jun 2016", "5038", "?");
AddRunInfo("25 Jun 2016", "5043", "275783");
AddRunInfo("26 Jun 2016", "5045", "275836");
AddRunInfo("28 Jun 2016", "5048", "?");


