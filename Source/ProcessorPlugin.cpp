/*
------------------------------------------------------------------

This file is part of the Open Ephys GUI
Copyright (C) 2022 Open Ephys

------------------------------------------------------------------

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ProcessorPlugin.h"
#include "PhoDatetimeTimestampHelper.h"
#include "PhoTimesyncFileHelper.h"

// #define DEBUGLOGGING 1
// #define DRYRUN 1
#define CUSTOMFILE 1

#include "ProcessorPluginEditor.h"


ProcessorPlugin::ProcessorPlugin() : GenericProcessor("PhoStartTimestampNew Processor"), curr_experiment_number(-1), isProcessing(false), isRecording(false), hasRecorded(false), needsWriteToCustomTimstampSyncFile(false), recordingStartSoftwareTimestamp(-1), recordingStartTime(std::chrono::system_clock::time_point()), pluginInitializationTime(std::chrono::system_clock::now())
{
	#ifdef DEBUGLOGGING
		CoreServices::sendStatusMessage("PhoProcessorPlugin::PhoProcessorPlugin(...)");
	#endif
}


ProcessorPlugin::~ProcessorPlugin()
{
	#ifdef CUSTOMFILE
		//TODO: this obviously shouldn't be here for efficiency reasons
		this->writeCustomTimestampFileIfNeeded();
	#endif
}

void ProcessorPlugin::writeCustomTimestampFileIfNeeded()
{
	#ifdef DEBUGLOGGING
		CoreServices::sendStatusMessage("PhoProcessorPlugin::writeCustomTimestampFileIfNeeded(...)");
	#endif
	// Called whenever a new data array is provided:
	if (needsWriteToCustomTimstampSyncFile) {
		#ifdef DRYRUN
			#ifdef DEBUGLOGGING
				CoreServices::sendStatusMessage("\t PhoProcessorPlugin::writeCustomTimestampFileIfNeeded(...): not writing file out because this is a dry-run, change #define DRYRUN 1 line.");
			#endif

			bool wasWritingSuccess = true;
		#else
			bool wasWritingSuccess = PhoTimesyncFileHelperSpace::writeOutCustomFile(recordingStartTime, false, true);
			
		#endif
		if (wasWritingSuccess) {
			needsWriteToCustomTimstampSyncFile = false;
			#ifdef DEBUGLOGGING
				CoreServices::sendStatusMessage("\t PhoProcessorPlugin::writeCustomTimestampFileIfNeeded(...): Writing success!");
			#endif
		}
		else {
			// ERROR
			needsWriteToCustomTimstampSyncFile = false;
			#ifdef DEBUGLOGGING
				CoreServices::sendStatusMessage("\t PhoProcessorPlugin::writeCustomTimestampFileIfNeeded(...): ERROR: Couldn't succeed in writing out file, aborting custom file write anyway!");
			#endif
		}
	}
}


AudioProcessorEditor* ProcessorPlugin::createEditor()
{
    editor = std::make_unique<ProcessorPluginEditor>(this);
    return editor.get();
}


void ProcessorPlugin::updateSettings()
{


}


void ProcessorPlugin::process(AudioBuffer<float>& buffer)
{
    isProcessing = true;
    checkForEvents(true);

}


void ProcessorPlugin::handleTTLEvent(TTLEventPtr event)
{

}


void ProcessorPlugin::handleSpike(SpikePtr spike)
{

}


void ProcessorPlugin::handleBroadcastMessage(String message)
{

}


void ProcessorPlugin::saveCustomParametersToXml(XmlElement* parentElement)
{

}


void ProcessorPlugin::loadCustomParametersFromXml(XmlElement* parentElement)
{

}
