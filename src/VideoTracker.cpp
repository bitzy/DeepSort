/*
 * VideoTracker.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: zy
 */
#include "VideoTracker.h"
#include "opencv2/opencv.hpp"
#include "matching/tracker.h"
#include "feature/FeatureTensor.h"
using namespace cv;
using namespace std;

#define args_nn_budget 100
#define args_max_cosine_distance 0.2
#define args_min_confidence 0.3
#define args_nms_max_overlap 1.0


bool VideoTracker::run(const char* vpath, bool showSwitch){
	VideoCapture m_cap(vpath);
	if(!m_cap.isOpened()) {
		this->errorMsg = "Couldn't connect to WEBCAM.";
		return false;
	}

	tracker mytracker(args_max_cosine_distance, args_nn_budget);
	while(true) {
		Mat frame;
		m_cap >> frame;
		if(frame.empty() == true) {
			this->errorMsg = "Load from Video Error";
			break;
		}

		DETECTIONS detections;
		if(ModelDetection::getInstance()->getFrameDetections(frame, detections) == false) {
			this->errorMsg = "YOLOV2 get detection error!";
			return false;
		}
		ModelDetection::getInstance()->dataMoreConf(args_min_confidence, detections);
		ModelDetection::getInstance()->dataPreprocessing(args_nms_max_overlap, detections);

		//TENSORFLOW get rect's feature.
		if(FeatureTensor::getInstance()->getRectsFeature(frame, detections) == false) {
			this->errorMsg = "Tensorflow get feature failed!";
			return false;
		}


		mytracker.predict();
		mytracker.update(detections);
		std::vector<RESULT_DATA> result;
		for(Track& track : mytracker.tracks) {
			if(!track.is_confirmed() || track.time_since_update > 1) continue;
			result.push_back(std::make_pair(track.track_id, track.to_tlwh()));
		}

		if(!showSwitch) continue;
		char showMsg[10];
		for(unsigned int k = 0; k < detections.size(); k++) {
			DETECTBOX tmpbox = detections[k].tlwh;
			Rect rect(tmpbox(0), tmpbox(1), tmpbox(2), tmpbox(3));
			rectangle(frame, rect, Scalar(0,0,255), 4);
		}

		for(unsigned int k = 0; k < result.size(); k++) {
			DETECTBOX tmp = result[k].second;
			Rect rect = Rect(tmp(0), tmp(1), tmp(2), tmp(3));
			rectangle(frame, rect, Scalar(255, 255, 0), 2);
			sprintf(showMsg, "%d", result[k].first);
			putText(frame, showMsg, Point(rect.x, rect.y), CV_FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 0), 2);
		}
		imshow("DeepSortTracking", frame);
		waitKey(10);
	}//end while;
	return true;
}

bool VideoTracker::run_sequenceWithGT(const char* motDir, bool showSwitch) {
	tracker mytracker(args_max_cosine_distance, args_nn_budget);
	int min_frame_idx, max_frame_idx;
	videoLoad(motDir, min_frame_idx, max_frame_idx);
	//prepare data:
	if(ModelDetection::getInstance()->loadDataFromFile(motDir, true) == false) {
		this->errorMsg = "load detection data from MOT directory & model2.dat failed!";
		return false;
	}
	for (int i = min_frame_idx; i <= max_frame_idx; i++) {
		DETECTIONS detections;

		if(ModelDetection::getInstance()->getFrameDetections(i, detections) == false) {
			this->errorMsg = "ModelDetection not load MOT model data!";
			return false;
		}
		ModelDetection::getInstance()->dataMoreConf(args_min_confidence, detections);
		ModelDetection::getInstance()->dataPreprocessing(args_nms_max_overlap, detections);

		mytracker.predict();
		mytracker.update(detections);
		std::vector<RESULT_DATA> result;
		for (Track& track : mytracker.tracks) {
			if (!track.is_confirmed() || track.time_since_update > 1) continue;
			result.push_back(std::make_pair(track.track_id, track.to_tlwh()));
		}

		if(showSwitch == false) continue;
		char fname[255], showMsg[10];
		sprintf(fname, "%simg1/%06d.jpg", motDir, i);
		Mat image = imread(fname);
		for (unsigned int k = 0; k < detections.size(); k++) {
			DETECTBOX tmpbox = detections[k].tlwh;
			Rect rect(tmpbox(0), tmpbox(1), tmpbox(2), tmpbox(3));
			rectangle(image, rect, Scalar(0, 0, 255), 4);
		}
		for(unsigned int k = 0; k < result.size(); k++) {
			DETECTBOX tmp = result[k].second;
			Rect rect = Rect(tmp(0), tmp(1), tmp(2), tmp(3));
			rectangle(image, rect, Scalar(255, 255, 0), 2);
			sprintf(showMsg, "%d", result[k].first);
			putText(image, showMsg, Point(rect.x, rect.y), CV_FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 255, 0), 2);
		}
		imshow("DeepSortTracking", image);
		waitKey(10);
	}//end while;
	return true;
}

bool VideoTracker::run_sequence(const char* motDir, bool showSwitch) {
	tracker mytracker(args_max_cosine_distance, args_nn_budget);
	int min_frame_idx, max_frame_idx;
	videoLoad(motDir, min_frame_idx, max_frame_idx);
	if(ModelDetection::getInstance()->loadDataFromFile(motDir, false) == false) {
		this->errorMsg = "load detection data from MOT directory failed!";
		return false;
	}
	for (int i = min_frame_idx; i <= max_frame_idx; i++) {
		DETECTIONS detections;

		if(ModelDetection::getInstance()->getFrameDetections(i, detections) == false) {
			this->errorMsg = "ModelDetection not load MOT model data!";
			return false;
		}
		ModelDetection::getInstance()->dataMoreConf(args_min_confidence, detections);
		ModelDetection::getInstance()->dataPreprocessing(args_nms_max_overlap, detections);

		//TENSORFLOW get rect's feature.
		char fname[255];
		sprintf(fname, "%simg1/%06d.jpg", motDir, i);
		Mat image = imread(fname);
		if(FeatureTensor::getInstance()->getRectsFeature(image, detections) == false) {
			this->errorMsg = "Tensorflow get feature failed!";
			return false;
		}

		mytracker.predict();
		mytracker.update(detections);
		std::vector<RESULT_DATA> result;
		for (Track& track : mytracker.tracks) {
			if (!track.is_confirmed() || track.time_since_update > 1) continue;
			result.push_back(std::make_pair(track.track_id, track.to_tlwh()));
		}

		if(showSwitch == false) continue;
		char showMsg[10];
		for (unsigned int k = 0; k < detections.size(); k++) {
			DETECTBOX tmpbox = detections[k].tlwh;
			Rect rect(tmpbox(0), tmpbox(1), tmpbox(2), tmpbox(3));
			rectangle(image, rect, Scalar(0, 0, 255), 4);
		}
		for(unsigned int k = 0; k < result.size(); k++) {
			DETECTBOX tmp = result[k].second;
			Rect rect = Rect(tmp(0), tmp(1), tmp(2), tmp(3));
			rectangle(image, rect, Scalar(255, 0, 0), 2);
			sprintf(showMsg, "%d", result[k].first);
			putText(image, showMsg, Point(rect.x, rect.y), CV_FONT_HERSHEY_SIMPLEX, 0.8, Scalar(255, 0, 0), 2);
		}
		imshow("DeepSortTracking", image);
		waitKey(10);
	}//end while;
	return true;
}

std::string VideoTracker::showErrMsg() {
	return this->errorMsg;
}


void VideoTracker::videoLoad(string sequence_dir,int &min_frame_idx, int &max_frame_idx) {
#ifdef __unix__
	string img_dir = sequence_dir.append("img1/");
	min_frame_idx = 1;
	char cmd[200];
	sprintf(cmd, "ls %s/*.jpg | wc -l > /tmp/tmp.txt", img_dir.c_str());
	system(cmd);

	std::ifstream readfile("/tmp/tmp.txt");
	string res;
	readfile >> res;
	sscanf(res.c_str(), "%d", &max_frame_idx);
#elif _WIN32
	//windows sytem
	//find all *.jpg files && get min&max idx.
	//undo
#endif
}


