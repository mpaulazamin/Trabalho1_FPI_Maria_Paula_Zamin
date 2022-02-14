#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;

void invertVertical(cv::Mat& original, cv::Mat& modified)
{
    //Acess pixels values and inverts vertically the original image
    for(int row = 0; row < modified.size().height / 2; row++)
    {
        for(int col = 0; col < modified.size().width; col++)
        {
            modified.at<cv::Vec3b>(row, col) = original.at<cv::Vec3b>(modified.size().height - 1 - row, col);
            modified.at<cv::Vec3b>(modified.size().height - 1 - row, col) = original.at<cv::Vec3b>(row, col);
        }
    }

    //Shows originala and vertically interved image
    cv::imshow("Original image", original);
    cv::imshow("Vertically inverted image", modified);
    cv::waitKey(0);

    //Saves modified image to a filepath
    cv::imwrite("/home/ubuntu/images/verticalImage.jpg", modified);
}

void invertHorizontal(cv::Mat& original, cv::Mat& modified)
{
    //Acess pixels values and inverts horizontally the original image
    for(int row = 0; row < modified.size().height; row++)
    {
        for(int col = 0; col < modified.size().width / 2; col++)
        {
            modified.at<cv::Vec3b>(row, col) = original.at<cv::Vec3b>(row, modified.size().width - 1 - col);
            modified.at<cv::Vec3b>(row, modified.size().width - 1 - col) = original.at<cv::Vec3b>(row, col);
        }
    }

    //Shows original and horizontally inverted image
    cv::imshow("Original image", original);
    cv::imshow("Horizontally inverted image", modified);
    cv::waitKey(0);

    //Saves modified image to a filepath
    cv::imwrite("/home/ubuntu/images/horizontalImage.jpg", modified);
}

void grayscale(cv::Mat& original, cv::Mat& modified)
{
    //Acess pixels values and converts the original image to grayscale
    for(int r = 0; r < original.rows; r++)
    {
        for(int c = 0; c < original.cols; c++)
        {
            //Computes luminance (gray) and replaces each pixel value of each channel by the value of luminance
            float gray = original.at<cv::Vec3b>(r, c)[0] * 0.114  + original.at<cv::Vec3b>(r, c)[1] * 0.587 + original.at<cv::Vec3b>(r, c)[2] * 0.299;
            modified.at<cv::Vec3b>(r, c)[0] = gray;
            modified.at<cv::Vec3b>(r, c)[1] = gray;
            modified.at<cv::Vec3b>(r, c)[2] = gray;
        }
    }

    //Shows original and converted to grayscale image
    cv::imshow("Original image", original);
    cv::imshow("Grayscale image", modified);
    cv::waitKey(0);

    //Saves modified image to a filepath
    cv::imwrite("/home/ubuntu/images/grayscaleImage.jpg", modified);
}

void quantization(cv::Mat& original, cv::Mat& modified, int tones)
{
    //Acess pixels values and converts the original image to grayscale
    for(int r = 0; r < original.rows; r++)
    {
        for(int c = 0; c < original.cols; c++)
        {
            //Computes luminance (gray) and replaces each pixel value of each channel by the value of luminance
            float gray = original.at<cv::Vec3b>(r, c)[0] * 0.114  + original.at<cv::Vec3b>(r, c)[1] * 0.587 + original.at<cv::Vec3b>(r, c)[2] * 0.299;
            modified.at<cv::Vec3b>(r, c)[0] = gray;
            modified.at<cv::Vec3b>(r, c)[1] = gray;
            modified.at<cv::Vec3b>(r, c)[2] = gray;
        }
    }

    //Converts the 3D grayscale image to 1D grayscale image
    //I tried to do this without using opencv functions, but I it wasn't working
    cv::cvtColor(modified, modified, cv::COLOR_BGR2GRAY);

    //Locates minimum (t1) and maximum (t2) intensity values of the 1D grayscale image
    double t1, t2;
    cv::minMaxLoc(modified, &t1, &t2);

    //Creates variable tam_int
    int tam_int = t2 - t1 + 1;

    //Creates variable with the number of tones that the quantized image will have
    int n = tones;

    if (n >= tam_int)
    {
        cout << "Quntization is not necessary." << endl;
        cout << "Displaying grayscale image." << endl;
    }

    if (n < tam_int)
    {
        //Computes size of each bin
        float tb = tam_int / n;

        for(int i = 0; i < n; i++)
        {
            //Computes minimum and maximum intervals of each possible bin
            float min_tb = (t1 - 0.5) + tb * i;
            float max_tb = (t1 - 0.5) + tb * (i+1);

            for(int r = 0; r < modified.rows; r++)
            {
                for(int c = 0; c < modified.cols; c++)
                {
                    //Gets pixel value of the coordinate (r, c)
                    float pixelVal = modified.at<uint8_t>(r, c) * 1;

                    //Checks if the pixel value is in the interval [min_tb, max_tb]
                    //If true, replaces the pixel value to the center of the interval [min_tb, max_tb]
                    if((pixelVal >= min_tb) && (pixelVal <= max_tb))
                    {
                        float pixelNew = min_tb + (max_tb - min_tb) / 2;
                        modified.at<uint8_t>(r, c) = (int)pixelNew;
                    }
                }
            }
        }

        //Shows original and quantized image
        cv::imshow("Original image", original);
        cv::imshow("Quantized image", modified);
        cv::waitKey(0);

        //Saves modified image to a filepath
        cv::imwrite("/home/ubuntu/images/quantizedImage.jpg", modified);
    }
}

int main()
{

    //Filepath to read image
    string filepath = "/home/ubuntu/images/Underwater_53k.jpg";

    //Reads original image, stores to a Mat image and checks if it isn't empty
    cv::Mat original = cv::imread(filepath);
    if (original.empty())
    {
        cout << "Image could not be found." << endl;
    }

    //Saves original image with other extension
    cv::imwrite("/home/ubuntu/images/Underwater_53k.png");

    //Reads original image, stores to a Mat image and checks if it isn't empty
    //This Mat image will be used to modify the pixels during the operations
    cv::Mat modified = cv::imread(filepath);
    if (modified.empty())
    {
        cout << "Image could not be found." << endl;
    }

    //Selects an operation to perform
    //Please uncomment the operation you want to test

    //string operation = "verticalInvert";
    //string operation = "horizontalInvert";
    //string operation = "grayscale";
    string operation = "quantization";

    if(operation == "verticalInvert")
    {
        //Performs a vertical invert to the original image
        invertVertical(original, modified);
    }

    else if(operation == "horizontalInvert")
    {
        //Performs a horizontal invert to the original image
        invertHorizontal(original, modified);
    }

    else if(operation == "grayscale")
    {
        //Converts original image to grayscale
        grayscale(original, modified);
    }

    else if(operation == "quantization")
    {
        //Quantizes original image
        //The number of tones is specified into tones variable
        int tones = 10;
        quantization(original, modified, tones);
    }
}
