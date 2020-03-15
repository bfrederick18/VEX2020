/*
    while (true)
    {
        double pitch = master.get_analog(ANALOG_LEFT_Y) * 1.27f;
        double yaw = master.get_analog(ANALOG_RIGHT_X);
    
        leftFront = pitch + yaw;
        leftBack = pitch + yaw;
        rightFront = pitch - yaw;
        rightBack = pitch - yaw;

        leftIntake = (master.get_digital(DIGITAL_L1) * 127) + (master.get_digital(DIGITAL_L2) * -60) + (master.get_digital(DIGITAL_RIGHT) * -187);
        rightIntake = (master.get_digital(DIGITAL_L1) * 127) + (master.get_digital(DIGITAL_L2) * -60) + (master.get_digital(DIGITAL_RIGHT) * -187);        
 
        if (master.get_digital(DIGITAL_LEFT))
        {
            vObject = vision.get_by_sig(0, GREEN_SIG);
            if (master.get_digital(DIGITAL_B))
            {
                //vObject = vision.get_by_sig(0, GREEN_SIG);
                double yScale = 0.5f;
                double pScale = 0.5f;
                int tHeight = 100;
                double offSet = 0;

                double vYaw = (VISION_FOV_WIDTH / 2 - vObject.x_middle_coord + offSet) * yScale;
                double vPitch = (tHeight - vObject.height) * pScale;

                leftFront = vPitch - vYaw;
                leftBack = vPitch - vYaw;
                rightFront = vPitch + vYaw;
                rightBack = vPitch + vYaw;
            }
            else if (master.get_digital(DIGITAL_A))
            {
                arm.set_brake_mode(MOTOR_BRAKE_HOLD);
                for (int i = 0; i < arraySize; i++)
                {
                    for (int j = 0; j < motorCount; j++)
                    {
                        motors[j].move_velocity(powers[i][j]);
                    }
                    pros::Task::delay_until(&now, SDUPDATEMS);
                }
            }
            else if (master.get_digital(DIGITAL_X) && !fileOpen)
            {
                fputs("s ", sd_file);
                fileOpen = true;
            }
            else if (master.get_digital(DIGITAL_Y) && fileOpen)
            {
                fputs("e ", sd_file);
                fclose(sd_file);
                fileOpen = false;
 
                sd_file = fopen(path.c_str(), "r");
                fgets(data, dataSize, (FILE*)sd_file);
                fclose(sd_file);
 
                int powerRow = 0;
                int powerCol = 0;
                for (int i = 0; i < dataSize; i++)
                {
                    if (data[i] == 'e')
                        break;
                    else if (data[i] == 's')
                        continue;
    
                    else if (data[i] == ' ')
                    {
                        i++;
                        int tempPower = 0;
                        int negative = 1;
                        while (true)
                        {
                            if (data[i] != ' ' && data[i] != ';')
                            {
                                if (data[i] == '-')
                                {
                                    negative = -1;
                                }
                                else
                                {
                                    tempPower *= 10;
                                    tempPower += data[i] - 48;
                                }
                                i++;
                            }
                            else
                            {
                                tempPower *= negative;
                                powers[powerRow][powerCol] = tempPower;
                                i--;
                                powerCol++;
                                break;
                            }
                        }
                    }
                    else if (data[i] == ';')
                    {
                        powerRow++;
                        powerCol = 0;
                    }
                }
            }
        }
        else
        {
            if (master.get_digital(DIGITAL_UP))
            {
                int desiredDeg = 1650;
                tower = (desiredDeg - tower.get_position()) * 0.16;
                hasReset = false;
            }
            else if (master.get_digital(DIGITAL_DOWN) && !towerBumper.get_value())
            {
                tower = -127;
                hasReset = false;
            }
            else
            {
                if (towerBumper.get_value() && hasReset)
                {
                    tower = (restPos - tower.get_position()) * 0.4;
                }
                else if (towerBumper.get_value())
                {
                    tower = 0;
                    tower.set_zero_position(0);
                    hasReset = true;
                }
                else
                {
                    tower = (restPos - tower.get_position()) * 0.25;
                }
            }
        
            
            if (master.get_digital(DIGITAL_R1) && master.get_digital(DIGITAL_R2))
            {
                arm = (50 - arm.get_position()) * 0.3;
            }
            else if (master.get_digital(DIGITAL_R1))
            {
                arm = (500 - arm.get_position()) * 2;
            }
            else if (master.get_digital(DIGITAL_R2))
            {
                arm = (400 - arm.get_position()) * 2;
            }
            else
            {
                arm = 0;
            }

            if (master.get_digital(DIGITAL_A)) //NEW
            {
                driveForwardV(500, 300, StateType::Coast);
                driveForwardV(100, 250, StateType::Brake);
                driveSet(-14);

                //EXPAND
                while (arm.get_position() <= 200)
                {
                    arm = 127;

                    pros::delay(1);

                    afterAuton = true;
                }
                arm = 0;
            }

            if (fileOpen)
            {
                for (int i = 0; i < motorCount - 1; i++)
                {
                    fputs((std::to_string((int)motors[i].get_actual_velocity()) + " ").c_str(), sd_file);
                }
                fputs((std::to_string((int)motors[motorCount - 1].get_actual_velocity()) + "; ").c_str(), sd_file);
            }

            pros::Task::delay_until(&now, SDUPDATEMS);
        }
    }
*/