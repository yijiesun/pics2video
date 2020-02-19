#include <stdio.h>
#include "opencv2/opencv.hpp"
#include <sstream>
#include<io.h>
using namespace std;
using namespace cv;
void getFiles1(string path, vector<string>& files)
{
	//文件句柄  
	//long hFile = 0;  //win7
	intptr_t hFile = 0;   //win10
						  //文件信息  
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
		// "\\*"是指读取文件夹下的所有类型的文件，若想读取特定类型的文件，以png为例，则用“\\*.png”
	{
		do
		{
			//如果是目录,迭代之  
			//如果不是,加入列表  
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles1(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(path + "\\" + fileinfo.name);
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

int main(int argc, char* argv[])
{
	//vid_opticalFlowFarnebackProcess();
	std::string picAddress = "E:\\SIMIT\\2020_new_project\\zsxl\\dataset\\1\\1\\";
	std::string saveVideoName = "E:\\SIMIT\\2020_new_project\\zsxl\\dataset\\1\\2.avi";
	vector<string> files;
	getFiles1(picAddress.c_str(), files);

	Mat frame=imread(files[0]);
	VideoWriter writer;
	int myFourCC = CV_FOURCC('D', 'I', 'V', 'X'); //avi
	//int myFourCC =CV_FOURCC('m', 'p', '4', 'v')//mp4
	writer.open(saveVideoName, myFourCC,15, frame.size(),true);

	vector<string>::iterator it = files.begin();
	int cnt = 0;
	for (; it != files.end(); it++)
	{
		cout << cnt++ << " --> " << *it << endl;
		Mat src = imread(*it);
		writer.write(src);
		if (waitKey(20) > 0)break;
	}
	writer.release();
	return 0;
}