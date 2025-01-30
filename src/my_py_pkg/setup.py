from setuptools import setup

package_name = 'my_py_pkg'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='vincent-pc',
    maintainer_email='vncnt.mh@gmail.com',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            "py_node                        = my_py_pkg.my_first_node:main",
            "robot_news_station             = my_py_pkg.robot_news_station:main",
            "smartphone                     = my_py_pkg.smartphone:main",
            "number_publisher_py            = my_py_pkg.number_publisher:main",
            "number_counter_py              = my_py_pkg.number_counter:main",
            "add_two_ints_server_py         = my_py_pkg.add_two_ints_server:main ",
            "add_two_ints_client_no_oop_py  = my_py_pkg.add_two_ints_client_no_oop:main",
            "add_two_ints_client            = my_py_pkg.add_two_ints_client:main",
            "number_counter_server_py       = my_py_pkg.number_counter_server:main",
            "reset_number_count_service     = my_py_pkg.reset_number_service:main",
            "hardware_status_publisher_py   = my_py_pkg.hw_status_publisher:main",
            "led_panel_py                   = my_py_pkg.led_panel:main",
            "battery_py                     = my_py_pkg.battery:main"
        ],
    },
)
