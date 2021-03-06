#pragma once

#if defined EMTEST_LIB
	#define EMTEST_LIB_DLLSPEC Q_DECL_EXPORT
#else
	#define EMTEST_LIB_DLLSPEC Q_DECL_IMPORT
#endif

#include <QtCore/QTimer>
#include <math.h>

#include <QDebug>

namespace emulators
{
class Q_DECL_EXPORT MotorDevice : public QObject
{
	Q_OBJECT
public:
	explicit MotorDevice(QObject *parent = 0);
	~MotorDevice();

public slots:
	void resetEncoder();

	float readEncoder() const;

	void setPower(int const &value);
	int power() const;

protected:
	static int const timeout = 10;
	static constexpr double accelerate = 1.64; //mpss
	static constexpr double maxSpeedAbs = 1.8; // mps
	static constexpr float encPerRound = 395;
	static constexpr double diameter = 0.18; //meters
	static constexpr double pi()
	{
		return 4 * std::atan(1);
	}

	static constexpr double roundLength()
	{
		return pi() * diameter; //meters
	}

	int mPower;
	float mEncoderValue;
	double mDestSpeed;
	double mSpeed;
	double mDeviation;

	QTimer mUpdater;

	void adjustSpeed();

protected slots:
	void updateState();
};
}

