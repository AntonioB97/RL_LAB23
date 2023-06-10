#include "ros/ros.h"
#include "classwork4/fileservice.h"
#include <geometry_msgs/Pose.h>
#include <tf/transform_broadcaster.h>

using namespace std;

int main(int argc, char** argv) {
    ros::init(argc, argv, "client_broadcaster");
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<classwork4::fileservice>("trservice");
    string frame_a;
    string frame_b;
    
    classwork4::fileservice srv;
    cout << "Choose the frame a"<<endl;
    cin>>frame_a;
    cout << "Choose the frame b"<<endl;
    cin>>frame_b;
    srv.request.frame_a.data=frame_a;
    srv.request.frame_b.data=frame_b;


    ROS_INFO("Waiting for the client server");
	client.waitForExistence(); 
	ROS_INFO("Client server up now");


    if (!client.call(srv)) {
		ROS_ERROR("Error calling the service");
		return 1;
	}
    /* while(ros::ok()){

        }
        */
       
	//Just print the output
	cout << "Service output: " << srv.response.pose << endl;



    // ros::Rate r(50);
  
    return 0;
}
