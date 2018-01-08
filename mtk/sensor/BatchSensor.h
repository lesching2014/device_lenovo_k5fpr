/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to MediaTek Inc. and/or its licensors.
 * Without the prior written permission of MediaTek inc. and/or its licensors,
 * any reproduction, modification, use or disclosure of MediaTek Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 */
/* MediaTek Inc. (C) 2012. All rights reserved.
 *
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER ON
 * AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN MEDIATEK SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek Software")
 * have been modified by MediaTek Inc. All revisions are subject to any receiver's
 * applicable license agreements with MediaTek Inc.
 */

#ifndef ANDROID_BATCH_SENSOR_H
#define ANDROID_BATCH_SENSOR_H

#include <stdint.h>
#include <errno.h>
#include <sys/cdefs.h>
#include <sys/types.h>


#include "nusensors.h"
#include "SensorBase.h"
#include "InputEventReader.h"
#include "hwmsensor.h"

/*****************************************************************************/
struct input_event;

class BatchSensor : public SensorBase {

    enum {
        Accelerometer        = 0,
        MagneticField        = 1,
        Orientation              = 2,
        Gyro                     = 3,
        light                        = 4,
        proximity                = 5,
        pressure             = 6,
        temperature        = 7,
		Gravity = 8,
		LinearAccelerometer = 9,
		RotationVector = 10,
        Relativehumidity = 11,
        /* Ambienttemperature, */
        Uncalimagnetic = 13,
		GameRotationVector = 14,
        Uncaligyroscope = 15,
		SignificantMotion = 16,
		StepDetector = 17,
		StepCounter = 18,
		GeomagneticRotationVector = 19,
        Heartrate = 20,
        Tiltdetector = 21,
		/* Wakegesture,
		   Glancegesture,
		   Pickupgesture,
		   wristtiltgesture, */
        Pedometer = 34,
        InPocket = 35,
        Activity = 36,
        Pdr = 37,
        Freefall = 38,
        Uncaliaccelerometer = 39,
        Facedown = 40,
        Shake = 41,
        BringtoSee = 42,
        numSensors = 43,
    };

        int mEnabled;
        InputEventCircularReader mInputReader;
    int64_t mEnabledTime[numSensors];
    char input_sysfs_path[PATH_MAX];
    int input_sysfs_path_len;
    int mDataDiv[numSensors];
	int flushSensorReq[ID_SENSOR_MAX_HANDLE];
	bool mHasPendingEvent;
	int64_t mTimestampHi;

public:
    int mdata_fd;
    sensors_meta_data_event_t mPendingEvent;

            BatchSensor();
    virtual ~BatchSensor();

    virtual int readEvents(sensors_event_t* data, int count);
    virtual int setDelay(int32_t handle, int64_t ns);
    virtual int enable(int32_t handle, int enabled);
    virtual int batch(int handle, int flags, int64_t samplingPeriodNs, int64_t maxBatchReportLatencyNs);
    virtual int flush(int handle);
    void processEvent(int code, int value);
    void handleEvent(sensors_meta_data_event_t* data, hwm_sensor_data *sensors_data);
    int TypeToSensor(int type);
    void GetSensorDiv(int div[]);
	virtual bool hasPendingEvents() const;
    int FindDataFd();
};

/*****************************************************************************/

#endif  // ANDROID_BATCH_SENSOR_H
