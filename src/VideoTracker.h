/*
 * VideoTracker.h
 *
 *  Created on: Dec 15, 2017
 *      Author: zy
 */

#ifndef VIDEOTRACKER_H_
#define VIDEOTRACKER_H_
#include <string>

/**
 * VideoTracker
 *
 * run:
 * -vpath: the video's path.
 * -showSwitch: whether show the tracking result.
 *
 * run_sequenceWithGT:
 * -motDir: the path of MOT directory.
 * -showSwitch: show or not.
 *
 * run_sequence:
 * -motDir: the path of MOT directory.
 * -showSwitch: show or not.
 */
class VideoTracker {
public:
	bool run(const char* vpath, bool showSwitch);
	bool run_sequenceWithGT(const char* motDir, bool showSwitch);
	bool run_sequence(const char* motDir, bool showSwitch);
	std::string showErrMsg();

private:
	bool vShowFlag;
	std::string errorMsg;

	void videoLoad(std::string sequence_dir,int &min_frame_idx, int &max_frame_idx);
	std::string loadFromBUFFERFILE();
};


#endif /* VIDEOTRACKER_H_ */

