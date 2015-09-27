// 
// main.cpp
//
// Copyright (c) 2015. Peter Gusev. All rights reserved
//

#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <ndnrtc/simple-log.h>
#include <ndnrtc/ndnrtc-library.h>

using namespace ndnrtc;

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

	if (!configFile)
	{
		std::cout << "usage: " << argv[0] << " -c <config_file>" << std::endl;
		exit(1);
	}

	run(std::string(configFile));

	return 0;
}

void run(const std::string& configFile)
{
	ndnp = &(NdnRtcLibrary::getSharedInstance());
	std::cout << "load params from " << configFile << std::endl;

}


