#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>
#include <tf/LinearMath/Matrix3x3.h>
#include <tf/LinearMath/Vector3.h>
#include <geometry_msgs/Transform.h>

using namespace std;


tf::StampedTransform echo_transform;
tf::TransformListener *tf_listener;
tf::StampedTransform min_distance_trans;
int id;
double min_distance;


void listener(){
    // use tf_listener to get the transformation from camera_link to tag 0
    for (int i = 0; i<16;i++){
        
        /**
         * For part2, you should find the transformation from map_tag_0 to other map_tag. 
         * Please uncomment the code below
         */

        string parent_id = "map_tag_0";
        string child_id = "map_tag_" + std::to_string(i);
        /* ============================================================================== */

        /**
         * For part3, you shoud find the transformation from camera_link to other tag.
         * Please uncomment the code below and comment the code above.
         */

        // string parent_id = "camera_link";
        // string child_id = "tag_" + std::to_string(i);
        /* ============================================================================== */

        tf_listener->waitForTransform(child_id, parent_id, ros::Time::now(), ros::Duration(0.7));
        try {

            tf_listener->lookupTransform(parent_id, child_id, ros::Time(0), echo_transform);
            std::cout << "At time " << std::setprecision(16) << echo_transform.stamp_.toSec() << std::endl;
            cout << "Frame id:" << echo_transform.frame_id_ << ", Child id:" << echo_transform.child_frame_id_ << endl;
            double yaw, pitch, roll;
            echo_transform.getBasis().getRPY(roll, pitch, yaw);
            tf::Quaternion q = echo_transform.getRotation();
            tf::Vector3 v = echo_transform.getOrigin();
            std::cout << "- Translation: [" << v.getX() << ", " << v.getY() << ", " << v.getZ() << "]" << std::endl;
            std::cout << "- Rotation: in Quaternion [" << q.getX() << ", " << q.getY() << ", "
                    << q.getZ() << ", " << q.getW() << "]" << std::endl;
            
            /*
              Part2
              Please calucluate the distance from tag_0 to other tags.
            */ 
            // Hint:
            // double dist;
            // double x = v.x();
            // ...
            // more detail: http://docs.ros.org/en/jade/api/tf/html/c++/classtf_1_1Vector3.html

            /************************************************************** 
            //                                                           //
            //                                                           //
            //                 Student Implementation                    //
            //                                                           //
            //                                                           //
            **************************************************************/

            /*
              find the closet distance from the tag to camera_link (remember to modify the parent_id).  //
            */
            /************************************************************** 
            //                                                           //
            //                                                           //
            //                 Student Implementation                    //
            //                                                           //
            //                                                           //
            **************************************************************/

        }
        catch (tf::TransformException& ex)
        {
            std::cout << "Exception thrown:" << ex.what() << std::endl;
        }
	}

    /*  
        Part3
        Find the camera position from map_tag_0.
        Please uncomment the code below.
    */
    // string parent_id = "map_tag_0";
    // string child_id = "map_tag_" + std::to_string(id);
    // tf_listener->waitForTransform(child_id, parent_id, ros::Time::now(), ros::Duration(0.001));
    // try {

    //     tf_listener->lookupTransform(parent_id, child_id, ros::Time(0), echo_transform);
    //     tf::Transform localization_trans;
    //     /*
    //         Find transformation matrix from echo_transform and min_distance_trans.
    //     */
    //     /**************************************************************
    //     //                 Student Implementation                    //
    //     **************************************************************/
    //     cout << "=================================\n";
    //     cout << "*get the robot position*\n";
    //     cout << "rotation:\n";
    //     tf::Quaternion q = localization_trans.getRotation();
    //     cout << "[" << q.getX() << ", " << q.getY() << ", "<< q.getZ() << ", " << q.getW() << "]" << endl;
    //     tf::Vector3 v = localization_trans.getOrigin();
    //     cout << "translation:\n";
    //     cout << "[" << v.getX() << ", " << v.getY() << ", " << v.getZ() << "]" << endl;
    //     cout << "=================================\n";
    // }
    // catch (tf::TransformException& ex)
    // {
    //     std::cout << "Exception thrown:" << ex.what() << std::endl;
    // }
    return ;
}

int main(int argc, char** argv){
    ros::init(argc, argv, "apriltag_tf");
    ros::NodeHandle nh;
    ros::Subscriber tf_sub;
    // tf_sub = nh.subscribe("tf_static",16,&tf_cb);
    tf_listener = new tf::TransformListener();

    while (ros::ok())
    {
        ros::spinOnce();
        listener();
    }
    
    return 0;
}
