//
//  main.cpp
//  Pre_Process
//
//  Created by Rydge on 5/4/15.
//  Copyright (c) 2015 SHU. All rights reserved.
//

#include "header.h"

void detectation(vector <Point3D> &source)
{
    vector<Point3D>::iterator it;
    int depth_high=0, depth_1200=0, depth_1100 = 0, depth_1000 = 0, depth_900 = 0, depth_800 = 0, depth_700 = 0, depth_600 = 0;
    int depth_500 = 0, depth_low = 0;
    for (it = source.begin(); it != source.end(); it++)
    {
        if (it->z >= 1300)
            depth_high++;
        else
        {
            if (it->z >= 1200)
                depth_1200++;
            else
            {
                if (it->z >= 1100)
                    depth_1100++;
                else
                {
                    if (it->z >= 1000)
                        depth_1000++;
                    else
                    {
                        if (it->z >= 900)
                            depth_900++;
                        else
                        {
                            if (it->z >= 800)
                                depth_800++;
                            else
                            {
                                if (it->z >= 700)
                                    depth_700++;
                                else
                                {
                                    if (it->z >= 600)
                                        depth_600++;
                                    else
                                    {
                                        if (it->z >= 500)
                                            depth_500++;
                                        else
                                        {
                                            depth_low++;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            
        }
    }
    
    cout << "大于1200的有" << depth_high << endl;
    cout << "1200的有" << depth_1200 << endl;
    cout << "1100的有" << depth_1100 << endl;
    cout << "1000的有" << depth_1000 << endl;
    cout << "900的有" << depth_900 << endl;
    cout << "800的有" << depth_800 << endl;
    cout << "700的有" << depth_700 << endl;
    cout << "600的有" << depth_600 << endl;
    cout << "500的有" << depth_500 << endl;
    cout << "小于500的有" << depth_low << endl;
}

void prepare_detection()
{
    vector<Point3D> source;
    readPoint("D:\\BS\\eurecom\\source\\s1\\depth_0001_s1_LightOn.txt", source);
    detectation(source);
}


// get the main face data from the original data
void process(const char *filename, vector<Point3D> &source, vector<Point3D> &mark)
{
    FILE *fp;
    fp = fopen(filename, "w");
    vector<Point3D>::iterator it1;
    vector<Point3D>::size_type i = 2;
    int last_z = mark[i].z;

    int corner_x = mark[i].x - 25;  //up left corner.x
    int corner_y = mark[i].y - 30;  //up left corner.y
    
    cout<<"鼻子深度值为:  "<<mark[i].z<<endl;
    
    for (it1 = source.begin(); it1 != source.end(); it1++)
    {
        //以鼻子位置为中心，截取人脸范围，并且处理做深度分割处理
        if (abs(it1->x - mark[i].x) < 25 && (it1->y > mark[i].y-30) && (it1->y < mark[i].y+50))
        {
            if (abs(it1->z - mark[i].z) <= 50)
            {
                fprintf(fp, "%d %d %d",it1->x-corner_x,it1->y-corner_y,it1->z);
                last_z=it1->z;
            }
            else
            {
                fprintf(fp, "%d %d %d", it1->x, it1->y, it1->z);
            }

        }
    }
    fclose(fp);
}

void prepare_process()
{
    string sourcePath = "/Users/rydge/desktop/Current/BS/eurecom3/source/";
    string markPath = "/Users/rydge/desktop/Current/BS/eurecom3/mark/";
    vector<string> sourceFiles, markFiles;

    string SegPath = "/Users/rydge/desktop/Current/BS/eurecom3/seg/";
    string result_path;
    
    
    getFiles(sourcePath, sourceFiles);
    getFiles(markPath, markFiles);
    
    size_t size = sourceFiles.size();
    
//    string c;
    
    for (int i = 0; i < size; i++)
    {
        
//        ostringstream oss;
//        oss << (i+1);
//        c = oss.str();
        
        cout << (sourcePath+sourceFiles[i]).c_str() << endl;
        cout<< (markPath+markFiles[i]).c_str()<<endl;
        
        vector<Point3D> source;
        vector<Point3D> mark;
        readPoint((sourcePath+sourceFiles[i]).c_str(), source);
        readMarkPoint((markPath+markFiles[i]).c_str(), mark);
        
        result_path = SegPath + sourceFiles[i];
        
        process(result_path.c_str(), source, mark);
        cout << result_path.c_str() << endl;
    }
}


//void segmentation(const char *filename, vector<Point3D> &source, vector<Point3D> &mark)
//{
//    FILE *fp;
//    fp = fopen(filename, "w");
//    vector<Point3D>::iterator it1;
//    vector<Point3D>::size_type i = 2;
//    int last_z = mark[i].z;
//    cout << "鼻子的深度值为" << mark[i].z << endl;
//    for (it1 = source.begin(); it1 != source.end(); it1++)
//    {
//        if (abs(it1->z - mark[i].z) <= 50)
//        {
//            fprintf(fp, "%d %d %d\n", it1->x, it1->y, it1->z);
//            last_z = it1->z;
//        }
//        else
//        {
//            fprintf(fp, "%d %d %d\n", it1->x, it1->y, last_z);
//        }
//    }
//    
//    fclose(fp);
//}


//
//void prepare_segmentation()
//{
//    string sourcePath = "/Users/rydge/desktop/Current/BS/eurecom3/face_data/";
//    string markPath = "/Users/rydge/desktop/Current/BS/eurecom3/mark/";
//    vector<string> sourceFiles, markFiles;
//    string segPath = "/Users/rydge/desktop/Current/BS/eurecom3/seg/";
//    string result_path;
//    

//    getFiles(sourcePath, sourceFiles);
//    getFiles(markPath, markFiles);
//    
//    size_t size = sourceFiles.size();
//    
//    for (int i = 0; i < size; i++)
//    {
////        ostringstream oss;
////        oss << (i+1);
////        c = oss.str();
//        
//        vector<Point3D> source;
//        vector<Point3D> mark;
//        readSegPoint((sourcePath+sourceFiles[i]).c_str(), source);
//        readMarkPoint((markPath+markFiles[i]).c_str(), mark);
//        
//        result_path = segPath +sourceFiles[i];
//        segmentation(result_path.c_str(), source, mark);
//    }
//}

int main()
{
    
//    prepare_detection();
    prepare_process();
    
}