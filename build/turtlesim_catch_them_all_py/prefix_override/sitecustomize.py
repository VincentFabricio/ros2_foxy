import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/vincent-pc/ros2_foxy/install/turtlesim_catch_them_all_py'
