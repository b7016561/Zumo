#include "ZumoCompass.h"

ZumoCompass::ZumoCompass()
{
}

ZumoCompass::~ZumoCompass()
{
}

void ZumoCompass::Initialisation()
{
	SPRINT(Try initialisation of compass..);
	compass.init();
	compass.enableDefault();
	compass.writeReg(LSM303::CRB_REG_M, CRB_REG_M_2_5GAUSS); // +/- 2.5 gauss sensitivity to hopefully avoid overflow problems
	compass.writeReg(LSM303::CRA_REG_M, CRA_REG_M_220HZ);    // 220 Hz compass update rate

	SPRINT(Compass initialised..);

}

void ZumoCompass::Calibrate()
{

	float runningMinX, runningMinY, runningMaxX, runningMaxY;
	SPRINT(Calibrating compass..);

	//MotorsClass::GetMotorInstance().SetMotorSpeeds(RUN_SPEED, -RUN_SPEED);

	for (int index = 0; index < 70; index++)
	{
		// Take a reading of the magnetic vectors which is stored in compass.m
		compass.read();

		runningMinX = min(runningMinX, compass.m.x);
		runningMinY = min(runningMinY, compass.m.y);

		runningMaxX = max(runningMaxX, compass.m.x);
		runningMaxY = max(runningMaxY, compass.m.y);

		delay(50);
	}

	//MotorsClass::GetMotorInstance().SetMotorSpeeds(0, 0);

	compass.m_max.x = runningMaxX;
	compass.m_max.y = runningMaxY;
	compass.m_min.x = runningMinX;
	compass.m_min.y = runningMinY;

	SPRINT(Finished calibrating compass..);

}

float ZumoCompass::GetAngle()
{
	return AverageHeading();
}

float ZumoCompass::Heading(LSM303::vector<long> v)
{
	float x_scaled = 2.0 * (float)(v.x - compass.m_min.x) / (compass.m_max.x - compass.m_min.x) - 1.0;
	float y_scaled = 2.0 * (float)(v.y - compass.m_min.y) / (compass.m_max.y - compass.m_min.y) - 1.0;

	float angle = atan2(y_scaled, x_scaled) * 180 / M_PI;
	if (angle < 0)
		angle += 360;
	return angle;
}

float ZumoCompass::AverageHeading()
{
	LSM303::vector<long> avg = { 0, 0, 0 };

	for (int i = 0; i < 10; i++)
	{
		compass.read();
		avg.x += compass.m.x;
		avg.y += compass.m.y;
	}
	avg.x /= 10.0;
	avg.y /= 10.0;

	// avg is the average measure of the magnetic vector.
	return Heading(avg);
}

// Yields the angle difference in degrees between two 
float ZumoCompass::RelativeHeading(float fromHeading, float toHeading)
{
	float relativeHeading = toHeading - fromHeading;

	
	if (relativeHeading > 180)
		relativeHeading -= 360;
	if (relativeHeading < -180)
		relativeHeading += 360;

	return relativeHeading;
}

extern ZumoCompass Compass;
