// file to intialise the sensors according to the shape of the robot
void sensor_initialisation() {
  if(my_robot.sm_getShape() == 'l'){
    front_sensor_status = my_robot.module1_sensor_status(0);
    right_sensor_status = my_robot.module4_sensor_status(4);
    rear_sensor_status = my_robot.module3_sensor_status(0);
    left_sensor_status = my_robot.module1_sensor_status(10);
    movements();
    
  }
  if(my_robot.sm_getShape() == 'i'){
    front_sensor_status = my_robot.module1_sensor_status(0);
    right_sensor_status = my_robot.module1_sensor_status(4);
    rear_sensor_status = my_robot.module3_sensor_status(0);
    left_sensor_status = my_robot.module1_sensor_status(10);
    movements();
    
  }
  if(my_robot.sm_getShape() == 'o'){
    front_sensor_status = my_robot.module1_sensor_status(0);
    right_sensor_status = my_robot.module1_sensor_status(4);
    rear_sensor_status = my_robot.module3_sensor_status(6);
    left_sensor_status = my_robot.module4_sensor_status(0);
    movements();
    
  }
  

}
