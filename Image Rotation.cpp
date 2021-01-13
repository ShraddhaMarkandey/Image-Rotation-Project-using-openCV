#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;
int main(int argc, char** argv)
{
    Mat transpose;
    //reading image file in mat object
    Mat src = imread("C:/Users/91827/Desktop/Pictures/Grayscale.jpg",IMREAD_UNCHANGED);
    //if not opened correctly
    if (src.empty()) 
    {
        cout << "Could not open or find the image!" << endl;
        cin.get();
        return -1;
    }
    Point2f srcTri[3]; //point 2f object for input file
    srcTri[0] = Point2f(0.f, 0.f);
    srcTri[1] = Point2f(src.cols - 1.f, 0.f); //Before transformation selecting points
    srcTri[2] = Point2f(0.f, src.rows - 1.f);
    Point2f dstTri[3];//point 2f object for destination file
    dstTri[0] = Point2f(0.f, src.rows * 0.33f);
    //After transformation by certain angle and distance
    dstTri[1] = Point2f(src.cols*0.85f,src.rows*0.25f); 
    dstTri[2] = Point2f(src.cols*0.15f, src.rows*0.7f);
    //apply an affine transforation to image and storing it
    Mat warp_mat = getAffineTransform(srcTri, dstTri);
    Mat warp_dst = Mat::zeros(src.rows, src.cols, src.type());
    warpAffine(src, warp_dst, warp_mat, warp_dst.size());
    Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
    double angle;
    double scale = 0.9; //setting scale value
    cout << "Enter the angle [(+)for anticlockwise rotation and (-) for clockwise rotation] at which you want to rotate: ";
    cin >> angle;
    Mat rot_mat = getRotationMatrix2D(center, angle, scale);//rotating with some references and angle
    Mat warp_rotate_dst;
    warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());
    string windowName1 = "Source Image";
    string windowName2 = "Resultant Image";
    //displaying the windows
    imshow(windowName1, src);
    imshow(windowName2, warp_rotate_dst);
    waitKey(0);
    destroyWindow(windowName1);
    destroyWindow(windowName2);
    return 0;
}
