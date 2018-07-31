#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <ifm3d/camera.h>
#include <ifm3d/fg.h>
#include <ifm3d/image.h>

int main(int argc, const char **argv)
{
	auto cam = ifm3d::Camera::MakeShared();

	ifm3d::ImageBuffer::Ptr img = std::make_shared<ifm3d::ImageBuffer>();
	ifm3d::FrameGrabber::Ptr fg =
		std::make_shared<ifm3d::FrameGrabber>(
			cam, ifm3d::IMG_AMP | ifm3d::IMG_CART | ifm3d::IMG_RDIS);
	pcl::PointCloud<pcl::PointXYZI> *cloud;


	if (!fg->WaitForFrame(img.get(), 1000))
	{
		std::cerr << "Timeout waiting for camera!" << std::endl;
		return -1;
	}

	// Get pointer of cloud file from image buffer
	cloud = img->Cloud().get();

	// Save pcd file by pcl library
	pcl::io::savePCDFileASCII("test_pcd.pcd", *cloud);
	return 0;
}
