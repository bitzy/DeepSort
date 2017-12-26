#include "model.h"
#include <algorithm>


#include "../darkSrc/region_layer.h"
#include "../darkSrc/cost_layer.h"
#include "../darkSrc/utils.h"
#include "../darkSrc/parser.h"
#include "../darkSrc/box.h"
#include "../darkSrc/demo.h"
#include "../darkSrc/option_list.h"

#ifdef OPENCV
#include "opencv2/highgui/highgui_c.h"
#include "opencv2/core/core_c.h"
#include "opencv2/core/version.hpp"

#ifndef CV_VERSION_EPOCH
#include "opencv2/videoio/videoio_c.h"
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_MAJOR)""CVAUX_STR(CV_VERSION_MINOR)""CVAUX_STR(CV_VERSION_REVISION)
#pragma comment(lib, "opencv_world" OPENCV_VERSION ".lib")
#else
#define OPENCV_VERSION CVAUX_STR(CV_VERSION_EPOCH)""CVAUX_STR(CV_VERSION_MAJOR)""CVAUX_STR(CV_VERSION_MINOR)
#pragma comment(lib, "opencv_core" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_imgproc" OPENCV_VERSION ".lib")
#pragma comment(lib, "opencv_highgui" OPENCV_VERSION ".lib")
#endif

#endif

enum DETECTBOX_IDX {IDX_X = 0, IDX_Y, IDX_W, IDX_H };
ModelDetection *ModelDetection::instance = NULL;

ModelDetection *ModelDetection::getInstance()
{
	if (instance == NULL) {
		instance = new ModelDetection();
	}
	return instance;
}

/**
 * load image's rects data.
 * @fpath: the mot directory.
 * model file must have \n in each line.
 */
bool ModelDetection::loadDataFromFile(const char* motDir, bool withFeature) {
	if(this->loadFromFile == true) {
		//run time program can only execute one time for this function.
		return false;
	}

	std::string fname = motDir;
	if(withFeature) {
		fname.append("model2.dat");
	} else {
		//with groundtruth
		//deepsort generate .npy file is very important to tracking.
		fname.append("model2.dat");//det/det.txt
	}

	FILE* fp = fopen(fname.c_str(), "r");
	if(fp == NULL) return false;

	while(true) {
		DETECTION_ROW tmpRow;

		int frame_idx;
		float tmpValue, x, y, w, h;
		if(fscanf(fp, "%f,", &tmpValue) != 1) break;
		frame_idx = (int)tmpValue;

		fscanf(fp, "%*f,%f,%f,%f,%f,", &x, &y, &w, &h);
		tmpRow.tlwh = DETECTBOX(x, y, w, h);
		fscanf(fp, "%f,%*f,%*f,%*f", &tmpValue);
		tmpRow.confidence = tmpValue;

		if(withFeature) {//read feature from file;
			for(int i = 10; i < 138; i++) {
				fscanf(fp, ",%f", &tmpValue);
				tmpRow.feature[i-10] = tmpValue;
			}
		} else fscanf(fp, "%*[^\n]"); //skip the line;


		if(data.find(frame_idx) == data.end()) {
			DETECTIONS frameData;
			frameData.push_back(tmpRow);
			data.insert(make_pair(frame_idx, frameData));
		} else data[frame_idx].push_back(tmpRow);
		if(fscanf(fp, "\n") == -1) break;
	}
	fclose(fp);
	this->loadFromFile = true;
	return true;
}

bool ModelDetection::getFrameDetections(cv::Mat& frame, DETECTIONS& res) {
	//YOLOV2 get frame's detection;
	if(frame.empty()) return true;
	//	std::vector<cv::Rect> rects;

	//=======================================================================
	//	char* filename = "";
	//
	//	if(filename){
	//		strncpy(input, filename, 256);
	//		if (input[strlen(input) - 1] == 0x0d) input[strlen(input) - 1] = 0;
	//	} else {
	//		printf("Enter Image Path: ");
	//		fflush(stdout);
	//		input = fgets(input, 256, stdin);
	//		if(!input) exit(1);
	//		strtok(input, "\n");
	//	}
	//	image im = load_image_color(input,0,0);
	//=======================================================================
	IplImage src = frame;
	image im = ipl_to_image(&src);
	rgbgr_image(im);


	image sized = resize_image(im, net.w, net.h);
	layer l = net.layers[net.n-1];

	box *boxes = (box*)calloc(l.w*l.h*l.n, sizeof(box));
	float **probs = (float**)calloc(l.w*l.h*l.n, sizeof(float *));
	for(int j = 0; j < l.w*l.h*l.n; ++j) probs[j] = (float*)calloc(l.classes, sizeof(float *));

	float *X = sized.data;
	time=clock();
	network_predict(net, X);
	//printf("%s: Predicted in %f seconds.\n", input, sec(clock()-time));
	get_region_boxes(l, 1, 1, thresh, probs, boxes, 0, 0);
	if (nms) do_nms_sort(boxes, probs, l.w*l.h*l.n, l.classes, nms);

	//=======================================================================
	//	draw_detections(im, l.w*l.h*l.n, thresh, boxes, probs, names, alphabet, l.classes);
	//	save_image(im, "predictions");
	//	show_image(im, "predictions");
	//=======================================================================
	int num = l.w * l.h * l.n;
	for(int i = 0; i < num; ++i) {
		int classname = max_index(probs[i], l.classes);
		if(classname != 0) continue;
		float prob = probs[i][classname];
		if(prob <= thresh) continue;
		//		printf("%s: %.0f%%\n", names[classname], prob*100);

		box b = boxes[i];
		int left	= (b.x - b.w/2.)*im.w;
		int right	= (b.x + b.w/2.)*im.w;
		int top 	= (b.y - b.h/2.)*im.h;
		int bot 	= (b.y + b.h/2.)*im.h;
		left 	= (left < 0? 0:left);
		right 	= (right>im.w-1?im.w-1:right);
		top		= (top < 0? 0:top);
		bot 	= (bot > im.h-1?im.h-1:bot);
		//		cv::Rect r = cv::Rect(left, top, (right-left+1), (bot-top+1));
		//		rects.push_back(r);
		//		cv::rectangle(frame, r, cv::Scalar(0,0,255), 1);
		DETECTION_ROW tmpRow;
		tmpRow.confidence = prob;
		tmpRow.tlwh = DETECTBOX(left, top, (right-left+1), (bot-top+1));
		res.push_back(tmpRow);
	}

	free_image(im);
	free_image(sized);
	free(boxes);
	free_ptrs((void **)probs, l.w*l.h*l.n);

	return true;
}

bool ModelDetection::getFrameDetections(int frame_idx, DETECTIONS& res)
{
	if(this->loadFromFile == true) {
		res = data[frame_idx];
		return true;
	}
	return false;
}


void ModelDetection::dataMoreConf(float min_confidence, DETECTIONS &d)
{
	DETECTIONS::iterator it;
	for(it = d.begin(); it != d.end();) {
		if((*it).confidence < min_confidence) it = d.erase(it);
		else ++it;
	}
}

void ModelDetection::dataPreprocessing(float max_bbox_overlap, DETECTIONS &d)
{
	int size = int(d.size());
	if(size == 0) return;

	//generate idx:
	std::vector<int> idxs;
	idxs.reserve(size);

	std::vector<bool> idx_status;
	idx_status.reserve(size);
	for(size_t i = 0; i < size; ++i) {
		idxs.push_back(int(i));
		idx_status.push_back(false);        
	}

	//get areas:
	std::vector<double> areas;
	areas.reserve(size);
	for(size_t i = 0; i < size; ++i) {
		double tmp = (d[i].tlwh(IDX_W)+1)*(d[i].tlwh(IDX_H)+1);
		areas.push_back(tmp);
	}

	//sort idxs by scores ==>quick sort:
	_Qsort(d, idxs, 0, size-1);

	//get delete detections:
	std::vector<int> delIdxs;
	while(true) {//get compare idx;
		int i = -1;
		for(int j = size-1; j>0; --j) {
			if(idx_status[j] == false) {
				i = j;
				idx_status[i] = true;
			}
		}
		if(i == -1) break; //end circle

		//get standard area:
		int xx1 = d[idxs[i]].tlwh(IDX_X); //max
		int yy1 = d[idxs[i]].tlwh(IDX_Y); //max
		int xx2 = d[idxs[i]].tlwh(IDX_X) + d[idxs[i]].tlwh(IDX_W); //min
		int yy2 = d[idxs[i]].tlwh(IDX_Y) + d[idxs[i]].tlwh(IDX_H);//min
		for(size_t j = 0; j < size; j++) {
			if(idx_status[j] == true) continue;
			xx1 = int(d[idxs[j]].tlwh(IDX_X) > xx1?d[idxs[j]].tlwh(IDX_X):xx1);
			yy1 = int(d[idxs[j]].tlwh(IDX_Y) > yy1?d[idxs[j]].tlwh(IDX_Y):yy1);
			int tmp = d[idxs[j]].tlwh(IDX_X) + d[idxs[j]].tlwh(IDX_W);
			xx2 = (tmp < xx2? tmp:xx2);
			tmp = d[idxs[j]].tlwh(IDX_Y) + d[idxs[j]].tlwh(IDX_H);
			yy2 = (tmp < yy2?tmp:yy2);
		}
		//standard area = w*h;
		int w = xx2-xx1+1; w = (w > 0?w:0);
		int h = yy2-yy1+1; h = (h > 0?h:0);
		//get delIdx;
		for(size_t j = 0; j < size; j++) {
			if(idx_status[j] == true) continue;
			double tmp = w*h*1.0/areas[idxs[j]];
			if(tmp > max_bbox_overlap) {
				delIdxs.push_back(idxs[j]);
				idx_status[j] = true;
			}
		}//end
	}
	//delete from detections:
	for(size_t i = 0; i < delIdxs.size(); ++i) {
		DETECTIONS::iterator it = d.begin() + delIdxs[i];
		d.erase(it);
	}
}


image ModelDetection::ipl_to_image(IplImage* src)
{
	unsigned char *data = (unsigned char *)src->imageData;
	int h = src->height;
	int w = src->width;
	int c = src->nChannels;
	int step = src->widthStep;
	image out = make_image(w, h, c);
	int i, j, k, count=0;;

	for(k= 0; k < c; ++k){
		for(i = 0; i < h; ++i){
			for(j = 0; j < w; ++j){
				out.data[count++] = data[i*step + j*c + k]/255.;
			}
		}
	}
	return out;
}

//load detection data from outer file
ModelDetection::ModelDetection()
{
	this->loadFromFile = false;
	char* datacfg = "RUNNINGDATA/darknet_data/cfg/coco.data";
	char* cfgfile = "RUNNINGDATA/darknet_data/cfg/yolo.cfg";
	char* weightfile = "RUNNINGDATA/darknet_data/yolo.weights";
	//char* filename = "";
	thresh = 0.24;

	list *options = read_data_cfg(datacfg);
	char *name_list = option_find_str(options, "names", "data/names.list");
	names = get_labels(name_list);

	//alphabet = load_alphabet();
	net = parse_network_cfg_custom(cfgfile, 1);
	if(weightfile){
		load_weights(&net, weightfile);
	}
	set_batch_network(&net, 1);
	srand(2222222);

	char buff[256];
	input = buff;
	nms=.4;
}

void ModelDetection::_Qsort(DETECTIONS d, std::vector<int>& a, int low, int high)
{
	if(low >= high) return;
	int first = low;
	int last = high;

	int key_idx = a[first];
	while(first < last) {
		while(first < last && d[a[last]].confidence >= d[key_idx].confidence) --last;
		a[first] = a[last];
		while(first < last && d[a[first]].confidence <= d[key_idx].confidence) ++first;
		a[last] = a[first];
	}
	a[first] = key_idx;
	_Qsort(d, a, low, first-1);
	_Qsort(d, a, first+1, high);
}


DETECTBOX DETECTION_ROW::to_xyah() const
{//(centerx, centery, ration, h)
	DETECTBOX ret = tlwh;
	ret(0,IDX_X) += (ret(0, IDX_W)*0.5);
	ret(0, IDX_Y) += (ret(0, IDX_H)*0.5);
	ret(0, IDX_W) /= ret(0, IDX_H);
	return ret;
}

DETECTBOX DETECTION_ROW::to_tlbr() const
{//(x,y,xx,yy)
	DETECTBOX ret = tlwh;
	ret(0, IDX_X) += ret(0, IDX_W);
	ret(0, IDX_Y) += ret(0, IDX_H);
	return ret;
}

