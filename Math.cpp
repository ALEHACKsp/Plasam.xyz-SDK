#include "Math.h"

namespace Math
{
	void NormalizeAngles(QAngle& angles)
	{
		for (auto i = 0; i < 3; i++) {
			while (angles[i] < -180.0f) angles[i] += 360.0f;
			while (angles[i] >  180.0f) angles[i] -= 360.0f;
		}
	}
	//--------------------------------------------------------------------------------
	void ClampAngles(QAngle& angles)
	{
		if (angles.pitch > 89.0f) angles.pitch = 89.0f;
		else if (angles.pitch < -89.0f) angles.pitch = -89.0f;

		if (angles.yaw > 180.0f) angles.yaw = 180.0f;
		else if (angles.yaw < -180.0f) angles.yaw = -180.0f;

		angles.roll = 0;
	}
	//--------------------------------------------------------------------------------
	void VectorTransform(const Vector& in1, const matrix3x4_t& in2, Vector& out)
	{
		out[0] = in1.Dot(in2[0]) + in2[0][3];
		out[1] = in1.Dot(in2[1]) + in2[1][3];
		out[2] = in1.Dot(in2[2]) + in2[2][3];
	}
	//--------------------------------------------------------------------------------
	void AngleVectors(const QAngle &angles, Vector& forward)
	{
		float	sp, sy, cp, cy;

		DirectX::XMScalarSinCos(&sp, &cp, DEG2RAD(angles[0]));
		DirectX::XMScalarSinCos(&sy, &cy, DEG2RAD(angles[1]));

		forward.x = cp*cy;
		forward.y = cp*sy;
		forward.z = -sp;
	}
	//--------------------------------------------------------------------------------
	void AngleVectors(const QAngle &angles, Vector& forward, Vector& right, Vector& up)
	{
		float sr, sp, sy, cr, cp, cy;

		DirectX::XMScalarSinCos(&sp, &cp, DEG2RAD(angles[0]));
		DirectX::XMScalarSinCos(&sy, &cy, DEG2RAD(angles[1]));
		DirectX::XMScalarSinCos(&sr, &cr, DEG2RAD(angles[2]));

		forward.x = (cp * cy);
		forward.y = (cp * sy);
		forward.z = (-sp);
		right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right.y = (-1 * sr * sp * sy + -1 * cr *  cy);
		right.z = (-1 * sr * cp);
		up.x = (cr * sp * cy + -sr*-sy);
		up.y = (cr * sp * sy + -sr*cy);
		up.z = (cr * cp);
	}
	//--------------------------------------------------------------------------------
	void VectorAngles(const Vector& forward, QAngle& angles)
	{
		float	tmp, yaw, pitch;

		if (forward[1] == 0 && forward[0] == 0) {
			yaw = 0;
			if (forward[2] > 0)
				pitch = 270;
			else
				pitch = 90;
		}
		else {
			yaw = (atan2(forward[1], forward[0]) * 180 / DirectX::XM_PI);
			if (yaw < 0)
				yaw += 360;

			tmp = sqrt(forward[0] * forward[0] + forward[1] * forward[1]);
			pitch = (atan2(-forward[2], tmp) * 180 / DirectX::XM_PI);
			if (pitch < 0)
				pitch += 360;
		}

		angles[0] = pitch;
		angles[1] = yaw;
		angles[2] = 0;
	}
	//--------------------------------------------------------------------------------
	float GetFov(const QAngle& viewAngle, const QAngle& aimAngle)
	{
		QAngle delta = aimAngle - viewAngle;
		NormalizeAngles(delta);

		return sqrtf(powf(delta[0], 2.0f) + powf(delta[1], 2.0f));
	}
	//--------------------------------------------------------------------------------
	QAngle CalcAngle(Vector src, Vector dst)
	{
		QAngle angles;
		Vector delta = src - dst;

		Math::VectorAngles(delta, angles);

		return angles;
	}
	//--------------------------------------------------------------------------------
}