from setuptools import setup

package_name = 'turtlesim_catch_them_all_py'

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
            "controller_py      = turtlesim_catch_them_all_py.turtle_controller         :main",
            "controller_py_PID  = turtlesim_catch_them_all_py.turtle_controller_PID     :main",
            "spawner_py        = turtlesim_catch_them_all_py.turtle_spawner:main",
        ],
    },
)
