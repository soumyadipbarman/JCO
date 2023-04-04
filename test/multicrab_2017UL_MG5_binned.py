#!/usr/bin/env python
"""
This is a small script that does the equivalent of multicrab.
"""
import os
from optparse import OptionParser

from CRABAPI.RawCommand import crabCommand
from CRABClient.ClientExceptions import ClientException
from httplib import HTTPException

def getOptions():
        """
        Parse and return the arguments provided by the user.
        """
        usage = ("Usage: %prog --crabCmd CMD [--workArea WAD --crabCmdOpts OPTS]"
                 "\nThe multicrab command executes 'crab CMD OPTS' for each project directory contained in WAD"
                 "\nUse multicrab -h for help")
        parser = OptionParser(usage=usage)

        parser.add_option('-c', '--crabCmd',
                dest = 'crabCmd',
                default = '',
                help = "crab command",
                metavar = 'CMD')

        parser.add_option('-w', '--workArea',
                dest = 'workArea',
                default = '',
                help = "work area directory (only if CMD != 'submit')",
                metavar = 'WAD')

        parser.add_option('-m', '--crabCmdOpts',
                dest = 'crabCmdOpts',
                default = '',
                help = "options for crab command CMD",
                metavar = 'OPTS')

        (options, arguments) = parser.parse_args()



        if arguments:
                parser.error("Found positional argument(s): %s." % (arguments))
        if not options.crabCmd:
                parser.error("(-c CMD, --crabCmd=CMD) option not provided.")
        if options.crabCmd != 'submit':
                if not options.workArea:
                        parser.error("(-w WAR, --workArea=WAR) option not provided.")
                if not os.path.isdir(options.workArea):
                        parser.error("'%s' is not a valid directory." % (options.workArea))
        return options

def main():
        options = getOptions()
# The submit command needs special treatment.
        if options.crabCmd == 'submit':
        #--------------------------------------------------------
        # This is the base config:
        #--------------------------------------------------------
                from CRABClient.UserUtilities import config
                config = config()

                config.General.requestName = None
                config.General.workArea = 'crab_projects'
                config.General.transferOutputs = True
                config.General.transferLogs = True
                config.JobType.pluginName = 'Analysis'
                config.JobType.psetName = 'Run_QCD_test_106x_mc_cfg.py'
#               config.Data.ignoreLocality = True
                config.Data.inputDBS = 'global'
		config.JobType.inputFiles= [
"/afs/cern.ch/work/s/sobarman/private/JetChargeAnalysis_v4/CMSSW_10_6_20/src/Test/QCDEventShape/test/Summer19UL17_JRV2_MC_PtResolution_AK4PFchs.txt",
"/afs/cern.ch/work/s/sobarman/private/JetChargeAnalysis_v4/CMSSW_10_6_20/src/Test/QCDEventShape/test/Summer19UL17_JRV2_MC_SF_AK4PFchs.txt",
"/afs/cern.ch/work/s/sobarman/private/JetChargeAnalysis_v4/CMSSW_10_6_20/src/Test/QCDEventShape/test/Summer19UL17_V5_MC_UncertaintySources_AK4PFchs.txt"]


#               config.JobType.maxMemoryMB = 2500
		config.JobType.maxJobRuntimeMin = 2750
#               config.JobType.priority = 9999
#               config.Data.splitting = 'EventAwareLumiBased'
		config.JobType.numCores = 2
                config.Data.splitting = 'FileBased'
                config.Data.unitsPerJob = 1
#               config.Data.useParent = True
                config.Data.inputDataset = None
#               config.Data.splitting = 'LumiBased'
#               config.Data.splitting = 'Automatic'
#               config.Data.unitsPerJob = 20
#               config.Data.totalUnits = 30
                config.Data.outputDatasetTag = None
#                config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions18/13TeV/ReReco/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt'
#               config.Data.outLFNDirBase = '/store/user/%s/' % (getUsernameFromSiteDB())
		config.Data.outLFNDirBase = '/store/user/sobarman/JetCharge/Analysis'
                config.Data.publication = False
                config.JobType.allowUndistributedCMSSW = True
                #config.Site.storageSite = 'T2_IN_TIFR'
		config.Site.storageSite = 'T3_US_FNALLPC'

            # Will submit one task for each of these input datasets.
                inputDatasets = [
	#'/QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer19UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM',
	#'/QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer19UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM',
	#'/QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer19UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM',
	#'/QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer19UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM',
	#'/QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer19UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM',
	#'/QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer19UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM',
	#'/QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer19UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM',
	#'/QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer19UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM',
	#'/QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8/RunIISummer19UL17MiniAOD-106X_mc2017_realistic_v6-v2/MINIAODSIM'
	'/QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM',
	'/QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM',
	'/QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM',
	'/QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM',
	'/QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM',
	'/QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM',
	'/QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM',
	'/QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM',
	'/QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM']

    	  	requestName =['HT50to100_TuneCP5','HT100to200_TuneCP5','HT200to300_TuneCP5','HT300to500_TuneCP5','HT500to700_TuneCP5','HT700to1000_TuneCP5',
                               'HT1000to1500_TuneCP5','HT1500to2000_TuneCP5','HT2000toInf_TuneCP5']
                ireq = 0
                for inDS in inputDatasets: 
                        config.General.requestName = requestName[ireq]
                        ireq += 1
                        config.Data.inputDataset = inDS
                        config.Data.outputDatasetTag = '%s_%s' % (config.General.workArea, config.General.requestName)
                        # Submit.
                        try:
                                print "Submitting for input dataset %s" % (inDS)
                                crabCommand(options.crabCmd, config = config, *options.crabCmdOpts.split())
                        except HTTPException as hte:
                                print "Submission for input dataset %s failed: %s" % (inDS, hte.headers)
                        except ClientException as cle:
                                print "Submission for input dataset %s failed: %s" % (inDS, cle)
        elif options.workArea:
                for dir in os.listdir(options.workArea):
                        projDir = os.path.join(options.workArea, dir)
                        if not os.path.isdir(projDir):
                                continue
                        # Execute the crab command.
                        msg = "Executing (the equivalent of): crab %s --dir %s %s" % (options.crabCmd, projDir, options.crabCmdOpts)
                        print "-"*len(msg)
                        print msg
                        print "-"*len(msg)
                        try:
                                crabCommand(options.crabCmd, dir = projDir, *options.crabCmdOpts.split())
                        except HTTPException as hte:
                                print "Failed executing command %s for task %s: %s" % (options.crabCmd, projDir, hte.headers)
                        except ClientException as cle:
                                print "Failed executing command %s for task %s: %s" % (options.crabCmd, projDir, cle)
if __name__ == '__main__':
        main()
