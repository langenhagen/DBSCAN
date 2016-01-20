/***************************
Main cpp for testing OPTICS
***************************/

#include <conio.h>
#include <iostream>
#include <random>
#include <opencv2/opencv.hpp>

#include "DBSCAN/dbscan.hpp"

#include <barn_common.hpp>
#include <barn_open_cv_common.hpp>

using namespace cv;
using namespace std;


void main() {

    Mat_<Vec3b> testset = imread( "gauss.png");
    
    noise( testset, 0.05f, Vec3b(255,255,255));

    while(1) {

        float eps;
        unsigned int min_pts;
        cout << "epsilon: "; cin >> eps;
        cout << "min_pts: "; cin >> min_pts;


        cout << "Scanning " << testset.rows << " x " << testset.cols << " test set...\n";
        std::vector<DBSCAN::DataPoint> db;
        for( int r=0; r<testset.rows; ++r)
        for( int c=0; c<testset.cols; ++c) {
            if( r%50 == 0 && c==0)
                cout << r << " \t";

            if( testset( r, c)[0] > 128) {
                DBSCAN::DataPoint p;
                p.data().push_back( r);
                p.data().push_back( c);
                db.push_back( p);
            }
        }
        cout << endl;
        
        /*
        cout << "Shuffling...\n";
        std::random_shuffle ( db.begin(), db.end() );
        /**/

        imshow( "testset", testset);


        cout << "\nRunning DBSCAN with " << db.size() << " samples...\n";
        unsigned int n_clusters = DBSCAN::dbscan( db, eps, min_pts);
        cout << "done.\n";

        cout << "found " << n_clusters << " clusters.\n";


        Mat_<Vec3b> result( testset.rows, testset.cols, Vec3b(0,0,0));
        Mat_<Vec3b> clrmthsv(1,1);
        Mat_<Vec3b> clrmtrgb(1,1);
        for( auto it=db.begin(); it!=db.end(); ++it) {
            DBSCAN::DataPoint& p = *it;
            
            unsigned int cluster = p.cluster();

            clrmthsv(0,0) = Vec3b( (float)cluster/n_clusters*180, 255, 255);
            cvtColor( clrmthsv, clrmtrgb, CV_HSV2BGR);
            Vec3b color = clrmtrgb(0,0);

            if( cluster == 0)
                color = Vec3b( 50,50,50);

            result( p[0], p[1]) = color;
        }

        imshow("result", result);
        waitKey();
        destroyAllWindows();
        cout << "========================================\n";
    }
}