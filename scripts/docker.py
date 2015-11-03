#!/usr/bin/env python
import rospy
from std_msgs.msg import Int8


def getbit(x,b):
	return (x >> b) % 2


def convert_line_data(data):
	d = []
	for i in range(0,5):
		d.append(getbit(data,i))
	return d

def line_cb(data):
	print convert_line_data(data.data)

def listener():
    rospy.init_node('docker', anonymous=True)
    rospy.Subscriber("chatter", Int8, line_cb)

    rospy.spin()

if __name__ == '__main__':
    listener()

# http://www.instructables.com/id/Line-following-robot-with-PID-algorithm/