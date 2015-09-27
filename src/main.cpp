// 
// main.cpp
//
// Copyright (c) 2015. Peter Gusev. All rights reserved
//

#define NDN_LOGGING
#define NDN_TRACE
#define NDN_INFO
#define NDN_WARN
#define NDN_ERROR
#define NDN_DEBUG

#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <ndnrtc/simple-log.h>
#include <ndnrtc/ndnrtc-library.h>

#include "renderer.h"

using namespace ndnrtc;
using namespace ndnrtc::new_api;

static NdnRtcLibrary* ndnp = NULL;

void run(const std::string& configFile);

int main(int argc, char **argv)
{
	char *configFile = NULL;
	int index;
	int c;

	opterr = 0;
	while ((c = getopt (argc, argv, "c:")) != -1)
		switch (c)
		{
			case 'c':
				configFile = optarg;
				break;
			case '?':
				if (optopt == 'c')
					fprintf (stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint (optopt))
					fprintf (stderr, "Unknown option `-%c'.\n", optopt);
				else
					fprintf (stderr,
						"Unknown option character `\\x%x'.\n",
						optopt);
				return 1;
			default:
				abort ();
		}

	// remove this for now
#warning implement loading parameters from configuration files
	#if 0
	if (!configFile)
	{
		std::cout << "usage: " << argv[0] << " -c <config_file>" << std::endl;
		exit(1);
	}
	#endif

	run(std::string(configFile));

	return 0;
}

void run(const std::string& configFile)
{
	ndnp = &(NdnRtcLibrary::getSharedInstance());

	LogInfo("") << "loading params from " << configFile << "..." << std::endl;
	
	GeneralParams generalParams;
	{
		// to save performance on VM
		generalParams.loggingLevel_ = ndnlog::NdnLoggerDetailLevelDefault;
		generalParams.logFile_ = "ndnrtc.log";
		generalParams.logPath_ = "/tmp";
		generalParams.useTlv_ = true;
		generalParams.useRtx_ = true;
		generalParams.useFec_ = true;
		generalParams.useAudio_ = true;
		generalParams.useVideo_ = true;
		generalParams.useAvSync_ = true;
		generalParams.skipIncomplete_ = true;

		// out prefix in case of publishing
		generalParams.prefix_ = "/ndn/edu/ucla/remap";
		// NFD host
		generalParams.host_ = "localhost";

		LogInfo("") << "general configuration:\n" << generalParams << std::endl; 
	}

	GeneralConsumerParams consumerParams;
	{
		consumerParams.interestLifetime_ = 2000;
		consumerParams.bufferSlotsNum_ = 200;
		consumerParams.slotSize_ = 64000;
		consumerParams.jitterSizeMs_ = 300;

		LogInfo("") << "fetching configuration:\n" << consumerParams << std::endl;
	}

	MediaStreamParams streamParams;
	{
		streamParams.streamName_ = "movie";
		streamParams.type_ = MediaStreamParams::MediaStreamTypeVideo;
		streamParams.producerParams_.segmentSize_ = 1000;
		streamParams.producerParams_.freshnessMs_ = 0; // doesn't matter for fetching

		// thread params we want to fetch from
		VideoThreadParams *threadParams = new VideoThreadParams();
		threadParams->threadName_ = "mid";
		threadParams->coderParams_.codecFrameRate_ = 30;
		threadParams->coderParams_.gop_ = 30;
		threadParams->coderParams_.startBitrate_ = 1000;
		threadParams->coderParams_.maxBitrate_ = 10000;
		threadParams->coderParams_.encodeHeight_ = 720;
		threadParams->coderParams_.encodeWidth_ = 1280;
		threadParams->deltaAvgSegNum_ = 5;
		threadParams->deltaAvgParitySegNum_ = 2;
		threadParams->keyAvgSegNum_ = 30;
		threadParams->keyAvgParitySegNum_ = 5;

		streamParams.mediaThreads_.push_back(threadParams);
		LogInfo("") << "remote stream configuration:\n" << streamParams << std::endl;
	}

	std::string sessionPrefix = "/ndn/edu/byu/ndnrtc/user/freeculture";
	std::string threadToFetch = "mid";
	RendererInternal renderer;

	LogInfo("") << "initiating remote stream for " << sessionPrefix << std::endl;
	std::string streamPrefix = ndnp->addRemoteStream(sessionPrefix, threadToFetch, streamParams, generalParams, consumerParams, &renderer);
	LogInfo("") << "demo fetching from " << streamPrefix << " initiated..." << std::endl;

	sleep(30);
	
	// ndnp->removeRemoteStream();
	LogInfo("") << "demo fetching has been completed" << std::endl;

	return;
}


