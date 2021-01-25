/*
 * AdPlay/UNIX - OPL2 audio player
 * Copyright (C) 2001 - 2003 Simon Peter <dn.tlp@gmx.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  
 */

#include <ctime>

#include "serial.h"

SerialPlayer::SerialPlayer(const char *device, int baud)
{
	opl = new CSerialDuoOpl(device, baud);
	playerTime.tv_sec = 0;
	playerTime.tv_nsec = 0;
}

SerialPlayer::~SerialPlayer() {
	delete opl;
}

void SerialPlayer::frame() {
	struct timespec curTime;
	clock_gettime(CLOCK_MONOTONIC, &curTime);

	if(playerTime.tv_sec == 0 && playerTime.tv_nsec == 0) {
		// Initialize the player time on the first frame
		playerTime = curTime;
		p->update();
		return;
	}

	// Calculate the time of the next frame
	long period = 1000000000.0 / p->getrefresh();
	playerTime.tv_nsec += period;
	if(playerTime.tv_nsec > 1000000000) {
		playerTime.tv_nsec -= 1000000000;
		playerTime.tv_sec += 1;
	}

	// Check if that's still in the future
	struct timespec delta = diffTime(playerTime, curTime);
	if(delta.tv_nsec < 0 || delta.tv_sec < 0) {
		float late = -(1000.0f*delta.tv_sec + delta.tv_nsec/1000000.0f);
		printf("*** late %.03f ms\n", late);
	} else {
		nanosleep(&delta, NULL);
	}
	p->update();
}

static void addTimeTo(struct timespec &timeToUpdate, const struct timespec &delta)
{
	timeToUpdate.tv_nsec += delta.tv_nsec;
	if(timeToUpdate.tv_nsec >= 1000000000) {
		timeToUpdate.tv_nsec -= 1000000000;
		timeToUpdate.tv_sec += 1;
	}
}

struct timespec SerialPlayer::diffTime(const struct timespec &t1, struct timespec t2)
{
	/* Perform the carry for the later subtraction by updating y. */
	if (t1.tv_nsec < t2.tv_nsec) {
		long nsec = (t2.tv_nsec - t1.tv_nsec) / 1000000000 + 1;
		t2.tv_nsec -= 1000000000 * nsec;
		t2.tv_sec += nsec;
	}
	if (t1.tv_nsec - t2.tv_nsec > 1000000) {
		long nsec = (t1.tv_nsec - t2.tv_nsec) / 1000000000;
		t2.tv_nsec += 1000000000 * nsec;
		t2.tv_sec -= nsec;
	}

	/* Compute the time remaining to wait.
	   tv_nsec is certainly positive. */
	struct timespec result;
	result.tv_sec = t1.tv_sec - t2.tv_sec;
	result.tv_nsec = t1.tv_nsec - t2.tv_nsec;
	return result;
}

Copl *SerialPlayer::get_opl() {
	return opl;
}
