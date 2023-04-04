from CRABClient.UserUtilities import config
config = config()

#config.General.requestName = 'JetHT_Run2017B_UL2017'
#config.General.requestName = 'JetHT_Run2017C_UL2017'
#config.General.requestName = 'JetHT_Run2017D_UL2017'
#config.General.requestName = 'JetHT_Run2017E_UL2017'
config.General.requestName = 'JetHT_Run2017F_UL2017'

config.General.workArea = 'crab_projects'
config.General.transferOutputs = True
config.General.transferLogs = True
config.JobType.pluginName = 'Analysis'
config.JobType.allowUndistributedCMSSW = True
config.JobType.psetName = 'Run_QCD_test_106x_data_cfg.py'

config.JobType.inputFiles= ["/afs/cern.ch/work/s/sobarman/private/JetChargeAnalysis_v4/CMSSW_10_6_20/src/Test/QCDEventShape/test/Summer19UL17_JRV2_DATA_PtResolution_AK4PFchs.txt",
"/afs/cern.ch/work/s/sobarman/private/JetChargeAnalysis_v4/CMSSW_10_6_20/src/Test/QCDEventShape/test/Summer19UL17_JRV2_DATA_SF_AK4PFchs.txt",
"/afs/cern.ch/work/s/sobarman/private/JetChargeAnalysis_v4/CMSSW_10_6_20/src/Test/QCDEventShape/test/Summer19UL17_RunB_V5_DATA_UncertaintySources_AK4PFchs.txt",
"/afs/cern.ch/work/s/sobarman/private/JetChargeAnalysis_v4/CMSSW_10_6_20/src/Test/QCDEventShape/test/Summer19UL17_RunC_V5_DATA_UncertaintySources_AK4PFchs.txt",
"/afs/cern.ch/work/s/sobarman/private/JetChargeAnalysis_v4/CMSSW_10_6_20/src/Test/QCDEventShape/test/Summer19UL17_RunD_V5_DATA_UncertaintySources_AK4PFchs.txt",
"/afs/cern.ch/work/s/sobarman/private/JetChargeAnalysis_v4/CMSSW_10_6_20/src/Test/QCDEventShape/test/Summer19UL17_RunE_V5_DATA_UncertaintySources_AK4PFchs.txt",
"/afs/cern.ch/work/s/sobarman/private/JetChargeAnalysis_v4/CMSSW_10_6_20/src/Test/QCDEventShape/test/Summer19UL17_RunF_V5_DATA_UncertaintySources_AK4PFchs.txt",
]

#config.Data.inputDataset = '/JetHT/Run2017B-09Aug2019_UL2017-v1/MINIAOD'
#config.Data.inputDataset = '/JetHT/Run2017C-09Aug2019_UL2017-v1/MINIAOD'
#config.Data.inputDataset = '/JetHT/Run2017D-09Aug2019_UL2017-v1/MINIAOD'
#config.Data.inputDataset = '/JetHT/Run2017E-09Aug2019_UL2017-v1/MINIAOD'
#config.Data.inputDataset = '/JetHT/Run2017F-09Aug2019_UL2017-v1/MINIAOD'

#config.Data.inputDataset = '/JetHT/Run2017B-UL2017_MiniAODv2-v1/MINIAOD'
#config.Data.inputDataset = '/JetHT/Run2017C-UL2017_MiniAODv2-v1/MINIAOD'
#config.Data.inputDataset = '/JetHT/Run2017D-UL2017_MiniAODv2-v1/MINIAOD'
#config.Data.inputDataset = '/JetHT/Run2017E-UL2017_MiniAODv2-v1/MINIAOD'
config.Data.inputDataset = '/JetHT/Run2017F-UL2017_MiniAODv2-v1/MINIAOD'

config.Data.inputDBS = 'global'
config.Data.splitting = 'LumiBased'
config.Data.unitsPerJob = 15
config.Data.lumiMask = '/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions17/13TeV/Legacy_2017/Cert_294927-306462_13TeV_UL2017_Collisions17_GoldenJSON.txt'

config.Data.outLFNDirBase = '/store/user/sobarman/JetCharge/Analysis'
config.Data.publication = False

#config.Data.outputDatasetTag = 'crab_projects_JetHT_Run2017B_UL2017'
#config.Data.outputDatasetTag = 'crab_projects_JetHT_Run2017C_UL2017'
#config.Data.outputDatasetTag = 'crab_projects_JetHT_Run2017D_UL2017'
#config.Data.outputDatasetTag = 'crab_projects_JetHT_Run2017E_UL2017'
config.Data.outputDatasetTag = 'crab_projects_JetHT_Run2017F_UL2017'

#config.Data.publishDataName = 'May2015_Data_analysis'

#config.Site.storageSite = 'T2_IN_TIFR'
config.Site.storageSite = 'T3_US_FNALLPC'
