#include "input_files.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"

#include "DataFormats/FWLite/interface/Handle.h"
#include "DataFormats/FWLite/interface/ChainEvent.h"

#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/CTPPSReco/interface/TotemRPLocalTrack.h"
#include "DataFormats/CTPPSReco/interface/TotemRPUVPattern.h"
#include "DataFormats/CTPPSReco/interface/TotemRPCluster.h"
#include "DataFormats/TotemDigi/interface/TotemRPDigi.h"
#include "DataFormats/TotemDigi/interface/TotemVFATStatus.h"
#include "DataFormats/TotemRPDetId/interface/TotemRPDetId.h"

#include <vector>
#include <string>

//----------------------------------------------------------------------------------------------------

using namespace std;
using namespace edm;

//----------------------------------------------------------------------------------------------------

// defaults

double n_si = 3.;

double cut1_a = -1., cut1_c = 0., cut1_si = 0.20;
double cut2_a = -1., cut2_c = 0., cut2_si = 0.20;

#include "parameters.h"

//----------------------------------------------------------------------------------------------------

struct PotPlots
{
	vector<TH1D *> v_h_vfat_multiplicity_strip;
	vector<TH1D *> v_h_vfat_multiplicity_daq;

	vector<TH1D *> v_h_vfat_multiplicity_cluster;
	vector<TH1D *> v_h_vfat_cluster_size;

	TH1D *h_n_planes_on;
	TH1D *h_n_planes_on_U;
	TH1D *h_n_planes_on_V;

	vector<TH1D *> v_h_plane_dist;
	vector<TH1D *> v_h_plane_dist_no_cutoff;

	TH2D *h2_plane_corr_10;
	TH2D *h2_plane_corr_32;
	TH2D *h2_plane_corr_98;
	
	TH2D *h2_plane_corr_32_no_cutoff;

	TH1D *h_n_patterns_U;
	TH1D *h_n_patterns_V;

	TH2D *h2_y_vs_x;

	PotPlots()
	{
		Init();
	}

	void Init()
	{
		for (int idx = 0; idx < 40; ++idx)
		{
			v_h_vfat_multiplicity_strip.push_back(new TH1D("", ";strip multiplicity", 31, -0.5, 30.5));
			v_h_vfat_multiplicity_daq.push_back(new TH1D("", ";cluster multiplicity", 31, -0.5, 30.5));

			v_h_vfat_multiplicity_cluster.push_back(new TH1D("", ";cluster multiplicity", 31, -0.5, 30.5));
			v_h_vfat_cluster_size.push_back(new TH1D("", ";cluster size", 31, -0.5, 30.5));
		}

		h_n_planes_on = new TH1D("", ";N planes", 11, -0.5, 10.5);
		h_n_planes_on_U = new TH1D("", ";N planes U", 6, -0.5, 5.5);
		h_n_planes_on_V = new TH1D("", ";N planes V", 6, -0.5, 5.5);

		for (int idx = 0; idx < 10; ++idx)
		{
			v_h_plane_dist.push_back(new TH1D("", ";strip", 512, -0.5, 511.5));
			v_h_plane_dist_no_cutoff.push_back(new TH1D("", ";strip", 512, -0.5, 511.5));
		}

		h2_plane_corr_10 = new TH2D("", ";strip plane 0; strip plane 1", 200, 250.5, 450.5, 200, 250.5, 450.5);
		h2_plane_corr_32 = new TH2D("", ";strip plane 2; strip plane 3", 200, 250.5, 450.5, 200, 250.5, 450.5);
		h2_plane_corr_98 = new TH2D("", ";strip plane 8; strip plane 9", 200, 250.5, 450.5, 200, 250.5, 450.5);

		h2_plane_corr_32_no_cutoff = new TH2D("", ";strip plane 2; strip plane 3", 200, 250.5, 450.5, 200, 250.5, 450.5);
		
		h_n_patterns_U = new TH1D("", ";N patterns U", 8, -0.5, 7.5);
		h_n_patterns_V = new TH1D("", ";N patterns V", 8, -0.5, 7.5);

		h2_y_vs_x = new TH2D("", ";x;y", 400, 0., 20., 300, -15., +15.);
	}

	void Write()
	{
		char buf[100];

		TDirectory *d_top = gDirectory;
		
		TDirectory *d_vfat_dist = d_top->mkdir("vfat distributions");
		for (unsigned int pi = 0; pi < 10; ++pi)
		{
			sprintf(buf, "plane %u", pi);
			TDirectory *d_pl = d_vfat_dist->mkdir(buf);

			for (unsigned int vi = 0; vi < 4; ++vi)
			{
				sprintf(buf, "vfat %u", vi);
				TDirectory *d_vfat = d_pl->mkdir(buf);
				gDirectory = d_vfat;

				unsigned int idx = 4*pi + vi;

				v_h_vfat_multiplicity_strip[idx]->Write("h_multiplicity_strip");
				v_h_vfat_multiplicity_daq[idx]->Write("h_multiplicity_daq");
				v_h_vfat_multiplicity_cluster[idx]->Write("h_multiplicity_cluster");
				v_h_vfat_cluster_size[idx]->Write("h_cluster_size");
			}
		}

		gDirectory = d_top;
		h_n_planes_on->Write("h_n_planes_on");
		h_n_planes_on_U->Write("h_n_planes_on_U");
		h_n_planes_on_V->Write("h_n_planes_on_V");

		TDirectory *d_plane_dist = d_top->mkdir("plane distributions");
		gDirectory = d_plane_dist->mkdir("inclusive");
		for (int idx = 0; idx < 10; ++idx)
		{
			sprintf(buf, "h_dist_%i", idx);
			v_h_plane_dist[idx]->Write(buf);
		}

		gDirectory = d_plane_dist->mkdir("no cutoff");
		for (int idx = 0; idx < 10; ++idx)
		{
			sprintf(buf, "h_dist_%i", idx);
			v_h_plane_dist_no_cutoff[idx]->Write(buf);
		}

		TDirectory *d_plane_corr = d_top->mkdir("plane correlations");
		gDirectory = d_plane_corr->mkdir("inclusive");
		h2_plane_corr_10->Write("h2_plane_corr_10");
		h2_plane_corr_32->Write("h2_plane_corr_32");
		h2_plane_corr_98->Write("h2_plane_corr_98");

		gDirectory = d_plane_corr->mkdir("no cutoff");
		h2_plane_corr_32_no_cutoff->Write("h2_plane_corr_32");

		gDirectory = d_top;
		h_n_patterns_U->Write("h_n_patterns_U");
		h_n_patterns_V->Write("h_n_patterns_V");

		h2_y_vs_x->Write("h2_y_vs_x");
	}
};

//----------------------------------------------------------------------------------------------------

struct PotInfo
{
	unsigned int id;
	string name;

	PotPlots plots;

	void Process(const fwlite::ChainEvent &ev);

	void Write()
	{
		TDirectory *d_top = gDirectory;
		gDirectory = d_top->mkdir(name.c_str());

		plots.Write();

		gDirectory = d_top;
	}
};

//----------------------------------------------------------------------------------------------------

void PotInfo::Process(const fwlite::ChainEvent &ev)
{
	//-------------------- vfat status --------------------

	fwlite::Handle< DetSetVector<TotemVFATStatus> > vfat_status;
	vfat_status.getByLabel(ev, "totemRPRawToDigi", "RP");

	bool cut_off_present = false;
	for (const auto &ds : *vfat_status)
	{
		unsigned int plId = TotemRPDetId::rawToDecId(ds.detId());
		unsigned int rpId = plId / 10;
		unsigned int plNum = plId % 10;

		if (rpId != id)
			continue;

		if (plNum == 2 || plNum == 3)
		{
			for (const auto &s : ds)
			{
				if (s.isNumberOfClustersSpecified())
					cut_off_present = true;
			}
		}

		for (const auto &s : ds)
		{
			unsigned int idx = 4*plNum + s.getChipPosition();
			if (s.isNumberOfClustersSpecified())
				plots.v_h_vfat_multiplicity_daq[idx]->Fill(s.getNumberOfClusters());
		}
	}

	/*
	if (cut_off_present)
		return;
	*/

	//-------------------- digi --------------------

	fwlite::Handle< DetSetVector<TotemRPDigi> > digis;
	digis.getByLabel(ev, "totemRPRawToDigi", "RP");

	set<unsigned short> pl_dig, pl_dig_U, pl_dig_V;
	vector<unsigned int> vfat_mult;
	vfat_mult.assign(40, 0);
	for (const auto &ds : *digis)
	{
		unsigned int plId = TotemRPDetId::rawToDecId(ds.detId());
		unsigned int rpId = plId / 10;
		unsigned int plNum = plId % 10;

		if (rpId != id)
			continue;

		pl_dig.insert(plNum);
		
		if (TotemRPDetId::isStripsCoordinateUDirection(plId))
			pl_dig_U.insert(plNum);
		else
			pl_dig_V.insert(plNum);

		for (const auto &d : ds)
		{
			unsigned int strip = d.getStripNumber();
			unsigned int vfatIdx = strip / 128;

			plots.v_h_plane_dist[plNum]->Fill(strip);

			if (!cut_off_present)
				plots.v_h_plane_dist_no_cutoff[plNum]->Fill(strip);

			unsigned int idx= plNum*4 + vfatIdx;
			vfat_mult[idx]++;
		}
	}

	for (unsigned int idx = 0; idx < 40; ++idx)
		plots.v_h_vfat_multiplicity_strip[idx]->Fill(vfat_mult[idx]);

	for (const auto &ds1 : *digis)
	{
		unsigned int plId1 = TotemRPDetId::rawToDecId(ds1.detId());
		unsigned int rpId1 = plId1 / 10;
		unsigned int plNum1 = plId1 % 10;

		if (rpId1 != id)
			continue;

		for (const auto &ds2 : *digis)
		{
			unsigned int plId2 = TotemRPDetId::rawToDecId(ds2.detId());
			unsigned int rpId2 = plId2 / 10;
			unsigned int plNum2 = plId2 % 10;

			if (rpId2 != id)
				continue;

			for (const auto &d1 : ds1)
			{
				for (const auto &d2 : ds2)
				{
					if (plNum1 == 0 && plNum2 == 1)
						plots.h2_plane_corr_10->Fill(d1.getStripNumber(), d2.getStripNumber());
					if (plNum1 == 2 && plNum2 == 3)
						plots.h2_plane_corr_32->Fill(d1.getStripNumber(), d2.getStripNumber());
					if (plNum1 == 8 && plNum2 == 9)
						plots.h2_plane_corr_98->Fill(d1.getStripNumber(), d2.getStripNumber());

					if (plNum1 == 2 && plNum2 == 3 && !cut_off_present)
						plots.h2_plane_corr_32_no_cutoff->Fill(d1.getStripNumber(), d2.getStripNumber());
				}
			}
		}
	}

	plots.h_n_planes_on->Fill(pl_dig.size());
	plots.h_n_planes_on_U->Fill(pl_dig_U.size());
	plots.h_n_planes_on_V->Fill(pl_dig_V.size());

	//-------------------- clusters --------------------

	vector<unsigned int> vfat_clu_mult;
	vfat_clu_mult.assign(40, 0);

	fwlite::Handle< DetSetVector<TotemRPCluster> > clusters;
	clusters.getByLabel(ev, "totemRPClusterProducer");

	for (const auto &ds : *clusters)
	{
		unsigned int plId = TotemRPDetId::rawToDecId(ds.detId());
		unsigned int rpId = plId / 10;
		unsigned int plNum = plId % 10;

		if (rpId != id)
			continue;

		for (const auto &cl : ds)
		{
			unsigned int strip = cl.getCenterStripPosition();
			unsigned int vfatIdx = strip / 128;
			unsigned int idx= plNum*4 + vfatIdx;

			plots.v_h_vfat_cluster_size[idx]->Fill(cl.getNumberOfStrips());

			vfat_clu_mult[idx]++;
		}
	}

	for (unsigned int idx = 0; idx < 40; ++idx)
		plots.v_h_vfat_multiplicity_cluster[idx]->Fill(vfat_clu_mult[idx]);

	//-------------------- patterns --------------------

	fwlite::Handle< DetSetVector<TotemRPUVPattern> > patterns;
	patterns.getByLabel(ev, "totemRPUVPatternFinder");

	unsigned int n_pat_U=0, n_pat_V=0;
	for (const auto &ds : *patterns)
	{
		if (ds.detId() != id)
			continue;

		for (const auto &p : ds)
		{
			if (p.getProjection() == TotemRPUVPattern::projU)
				n_pat_U++;

			if (p.getProjection() == TotemRPUVPattern::projV)
				n_pat_V++;
		}
	}
	
	plots.h_n_patterns_U->Fill(n_pat_U);
	plots.h_n_patterns_V->Fill(n_pat_V);

	//-------------------- tracks --------------------

	fwlite::Handle< DetSetVector<TotemRPLocalTrack> > tracks;
	tracks.getByLabel(ev, "totemRPLocalTrackFitter");

	for (const auto &ds : *tracks)
	{
		if (ds.detId() != id)
			continue;

		for (const auto &t : ds)
		{
			if (t.isValid())
				plots.h2_y_vs_x->Fill(t.getX0(), t.getY0());
		}
	}
}

//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------

int main()
{
	// apply settings
	ApplySettings();

	vector<PotInfo *> potInfo;
	for (auto rpId : {3, 2, 102, 103})
	{
		PotInfo* info = new PotInfo;

		info->id = rpId;

		char buf[100];
		sprintf(buf, "%u", rpId);
		info->name = buf;

		potInfo.push_back(info);
	}

	// get input
	InitInputFiles();
	fwlite::ChainEvent ev(input_files);

	// ouput file
	TFile *f_out = new TFile("distributions.root", "recreate");

	// loop over the chain entries
	unsigned int ev_count = 0;
	for (ev.toBegin(); ! ev.atEnd(); ++ev)
	{
		/*
		if (ev_count > 10000)
			break;
		ev_count++;
		*/

		for (auto &info : potInfo)
			info->Process(ev);
	}

	// save histograms
	gDirectory = f_out;
	for (auto &info : potInfo)
		info->Write();

	// clean up
	delete f_out;
	return 0;
}
