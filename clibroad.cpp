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
    tf::TransformBroadcaster br;
    tf::Transform transform;
    tf::Quaternion q;
    classwork4::fileservice srv;
    cout << "Service inserire il frame a"<<endl;
    cin>>frame_a;
    cout << "Service inserire il frame b"<<endl;
    cin>>frame_b;



    ROS_INFO("Waiting for the client server");
	client.waitForExistence(); 
	ROS_INFO("Client server up now");

    while(ros::ok()){
    if (!client.call(srv)) {
		ROS_ERROR("Error calling the service");
		return 1;
	}
     srv.request.frame_a.data=frame_a;
     srv.request.frame_b.data= frame_b;
    
	//Just print the output
	cout << "Service output: " << srv.response.pose << endl;
     transform.setOrigin( tf::Vector3(srv.response.pose.position.x,srv.response.pose.position.y,srv.response.pose.position.z));
     q.setRPY(srv.response.pose.orientation.x,srv.response.pose.orientation.y,srv.response.pose.orientation.z);
     transform.setRotation(q);
     br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), frame_a,frame_b));




     ros::Rate r(10);
     }
  
    return 0;
}
