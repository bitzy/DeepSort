#include <iostream>
#include "VideoTracker.h"
using namespace std;

#define MOTDIR "/home/zy/git-project/MOT_tracking/deep_sort/MOT16/test/MOT16-06/"
#define VIDEO "./RUNNINGDATA/test.avi"
//#define RUNGT
//#define RUNMOTTENSOR
#define RUNLOCALVIDEO

int main()
{
	VideoTracker* t = new VideoTracker;
#ifdef RUNGT
	if(t->run_sequenceWithGT(MOTDIR, true) == false) {
		cout << t->showErrMsg() << endl;
	}
#endif

#ifdef RUNMOTTENSOR
	if(t->run_sequence(MOTDIR, true) == false) {
		cout << t->showErrMsg() << endl;
	}
#endif

#ifdef RUNLOCALVIDEO
	if(t->run(VIDEO, true) == false) {
		cout << t->showErrMsg() << endl;
	}
#endif
	return 0;
}
